#include <Fantasy2C/SimpleSprite.hpp>

namespace F2C{

int16 SimpleSprite::render() const{
    if(!this->show)
         return -1;

    //if: Alpha Color == 0
    if(this->vColor[0].alpha < 1 &&
        this->vColor[1].alpha < 1 &&
        this->vColor[2].alpha < 1 &&
        this->vColor[3].alpha < 1){
            return -4;
    }

    //if: Zoom-Factor == 0
    if(this->zoom_x == 0.0f || this->zoom_y == 0.0f)
        return -5;

    GLdouble texW = 0;
    GLdouble texH = 0;
    Rect srect = this->src_rect;

    if(this->bitmapWidth > 0 || this->bitmapHeight > 0){
        if (srect.width == 0)
            srect.width = this->bitmapWidth;
        if (srect.height == 0)
            srect.height = this->bitmapHeight;
        texW = this->pixelsWidth;
        texH = this->pixelsWidth;
    }else{
        texW = this->src_rect.width;
        texH = this->src_rect.height;
    }
    if(texW == 0 || texH == 0)
        return -2;

    if(!RenderManager::isInViewportRange(this->x,this->y,srect.width,srect.height))
        return -3;

    //Array of texcoord,vertices and colors
    //texcoord = {x,y,            width,y,
    //            width,height,   x,height}
    //vertices = {x,y,z,            width,y,z,
    //            width,height,z,   x,height,z}
    //vcolors =  {r,g,b,a,        r,g,b,a,
    //            r,g,b,a,        r,g,b,a}
    GLdouble texcoord[8] = {0};
    GLdouble vertices[12] = {0};
    GLubyte vcolors[16] = {0};

    RenderManager::getTexCoordArray8(texcoord,srect,texW,texH);
    RenderManager::getVerticesArray12(vertices,0,0,0,srect.width,srect.height);

    if(this->flippedH){
        RenderManager::flippedHTexCoord8(texcoord);
    }
    if(this->flippedV){
        RenderManager::flippedVTexCoord8(texcoord);
    }

    RenderManager::enable2DTexture(this->pixels != NULL);
    RenderManager::bindTexture(this->texture);
    RenderManager::setTexParam(this->filter);
    RenderManager::setBlendFunc(this->blend_type);
    RenderManager::setCoord(this->x,this->y,this->z*100.0f,
                            srect.width,srect.height,
                            this->angle_x,this->angle_y,this->angle_z,
                            this->zoom_x,this->zoom_y);

    if(!this->ShaderProgramObj || this->grayscale < 255){
        RenderManager::getColorArray4(vcolors,this->vColor,4,4);
        RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,1,SimpleSprite::VertexArray);
    }
    if(this->ShaderProgramObj && this->grayscale > 0){
        Color newvColors[4];
        for(size_t i = 0;i < 4;++i)
            newvColors[i].set(255,255,255,std::min<GLubyte>(this->vColor[i].alpha,this->grayscale));

        RenderManager::getColorArray4(vcolors,newvColors,4,4);

        glUseProgramObjectARB( this->ShaderProgramObj );
        RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,1,SimpleSprite::VertexArray);
        glUseProgramObjectARB( 0 );
    }

    RenderManager::enable2DTexture(false);

	return 1;
}

}
