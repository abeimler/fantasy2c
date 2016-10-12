#include <Fantasy2C/Sprite.hpp>

namespace F2C{

int16 Sprite::render() const{
    //if: show == false
    if (this->viewport){
      if(!this->viewport->show){
         return -1;
      }
    }
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

    //width of Texture
    GLdouble texW = 0.0f;

    //height of Texture
    GLdouble texH = 0.0f;

    //source Rect of Texture
    Rect srect = this->src_rect;

    //set Texture Size: Bitmap or simple Rect(with this->src_rect)
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

    //set srect: Minimal and Maximal Values
    if(this->bitmapWidth > 0)
        srect.width = std::min<uint>(this->bitmapWidth,srect.width);
    if(this->bitmapHeight > 0)
        srect.height = std::min<uint>(this->bitmapHeight,srect.height);

    if( srect.x > static_cast<int>(this->bitmapWidth)){ srect.x = static_cast<int>(this->bitmapWidth);}
    else if( srect.x < 0 ){srect.x = 0;}
    if( srect.y > static_cast<int>(this->bitmapHeight)){ srect.y = static_cast<int>(this->bitmapHeight);}
    else if( srect.y < 0 ){srect.y = 0;}

    //if: outside of clipping Rect or Display
    if(this->clip_rect){
        if(!RenderManager::iscollisionRect(Rect (this->x,this->y,srect.width,srect.height), *this->clip_rect))
            return -3;
    }else{
        if(!RenderManager::isInViewportRange(this->x,this->y,srect.width,srect.height))
            return -3;
    }

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

    if(this->clip_rect){
        RenderManager::enableScissor(true);
        RenderManager::setScissorInTopLeftMode(*this->clip_rect);
    }

    RenderManager::enable2DTexture(this->pixels != NULL);
    RenderManager::bindTexture(this->texture);
    RenderManager::setTexParam(this->filter);
    RenderManager::setBlendFunc(this->blend_type);
    RenderManager::setCoord(this->x,this->y,
                            (this->z + ((this->viewport)? this->viewport->z : 0.0f))*100.0f,
                            srect.width,srect.height,
                            this->angle_x,this->angle_y,this->angle_z,
                            this->zoom_x,this->zoom_y);

    /**
    *Rendering
    * 1. Fill Stencil Buffer and normal Texture rendering
    * 2. Rect with this->tone Color rendering
    * 3. Rect with this->viewport->tone Color rendering
    * 4. grayscale Texture rendering
    */

    bool isneedstencil = false;
    if(this->viewport){
        //needed by tonecolor or (viewport)tonecolor
        isneedstencil = (this->tone.getRed() != 0 || this->tone.getGreen() != 0 || this->tone.getBlue() != 0) ||
                            (this->viewport->tone.getRed() != 0 || this->viewport->tone.getGreen() != 0 || this->viewport->tone.getBlue() != 0);
    }else{
        //only needed by tonecolor
        isneedstencil = this->tone.getRed() != 0 || this->tone.getGreen() != 0 || this->tone.getBlue() != 0;
    }

    RenderManager::enableStencil(isneedstencil);
    if(!this->ShaderProgramObj || this->tone.grayscale < 255){
        //normal rendering
        if(isneedstencil){
            //start Stencil
            RenderManager::startStencil();
        }

        RenderManager::getColorArray4(vcolors,this->vColor,4,4);
        RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,1,Sprite::VertexArray);

        if(isneedstencil){
            RenderManager::endStencil();
        }

        //rendering with tonecolor
        if(this->tone.getRed() != 0 || this->tone.getGreen() != 0 || this->tone.getBlue() != 0){
            RenderManager::enable2DTexture(false); //only color needed
            RenderManager::setBlendFunc(BlendType::additives);

            GLubyte rgb[3] = {0};
            ColorTone::ColorTonetoRGB(this->tone,rgb);
            Color newvColors[4];
            for(size_t i = 0;i < 4;++i)
                newvColors[i].set(rgb[0],rgb[1],rgb[2],this->vColor[i].alpha);

            RenderManager::getColorArray4(vcolors,newvColors,4,4);
            RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,1,Sprite::VertexArray);
        }

        //rendering with (viewport) tonecolor
        if(this->viewport){
            if(this->viewport->tone.getRed() != 0 || this->viewport->tone.getGreen() != 0 || this->viewport->tone.getBlue() != 0){
                RenderManager::enable2DTexture(false); //only color needed
                RenderManager::setBlendFunc(BlendType::additives);

                GLubyte rgb[3] = {0};
                ColorTone::ColorTonetoRGB(this->viewport->tone,rgb);
                Color newvColors[4];
                for(size_t i = 0;i < 4;++i)
                    newvColors[i].set(rgb[0],rgb[1],rgb[2],this->vColor[i].alpha);

                RenderManager::getColorArray4(vcolors,newvColors,4,4);
                RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,1,Sprite::VertexArray);
            }
        }
    }
    if(isneedstencil){
        RenderManager::clearStencil();
        RenderManager::enableStencil(false);
    }

    RenderManager::enable2DTexture(this->pixels != NULL);
    RenderManager::setBlendFunc(this->blend_type);
    if(this->ShaderProgramObj && this->tone.grayscale > 0){
        Color newvColors[4];
        for(size_t i = 0;i < 4;++i)
            newvColors[i].set(255,255,255,std::min<GLubyte>(this->vColor[i].alpha,this->tone.grayscale));

        RenderManager::getColorArray4(vcolors,newvColors,4,4);

        glUseProgramObjectARB( this->ShaderProgramObj );
        RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,1,Sprite::VertexArray);
        glUseProgramObjectARB( 0 );
    }

    if(this->clip_rect)
            RenderManager::enableScissor(false);
    RenderManager::enable2DTexture(false);

    return 1;
}
}
