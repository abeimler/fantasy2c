#include <Fantasy2C/Plane.hpp>

namespace F2C{

int16 Plane::render() const{
    //if: show == false

    if (this->viewport){
      if(!viewport->show){
         return -1;
      }else if(!this->show)
         return -1;
    }else{
      if(!this->show)
         return -1;
    }

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
    GLdouble texW = 0;
    //height of Texture
    GLdouble texH = 0;

    //source rect of first Texture
    Rect srect = this->src_rect;

    //source rect of full Texture
    Rect fullsrect (0,0,this->bitmapWidth,this->bitmapHeight);

    //Size of Plane
    Rect bgrect = this->src_rect;

    //if: Bitmap exists
    //set Texture Size
    if(this->bitmapWidth > 0 || this->bitmapHeight > 0){
        if (bgrect.width == 0)
            bgrect.width = this->bitmapWidth;
        if (bgrect.height == 0)
            bgrect.height = this->bitmapHeight;
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

    //set maximal and minimal values of srect
    if(this->bitmapWidth > 0)
        srect.width = std::min<uint>(this->bitmapWidth,srect.width);
    if(this->bitmapHeight > 0)
        srect.height = std::min<uint>(this->bitmapHeight,srect.height);

    if( srect.x > static_cast<int>(this->bitmapWidth)){ srect.x = srect.x % static_cast<int>(this->bitmapWidth);}
    if( srect.x < 0 ){srect.x = static_cast<int>(this->bitmapWidth) + srect.x;}

    if( srect.y > static_cast<int>(this->bitmapHeight)){ srect.y = srect.y % static_cast<int>(this->bitmapHeight);}
    if( srect.y < 0 ){srect.y = static_cast<int>(this->bitmapHeight) + srect.y;}

    //if: outside of clipping Rect or Display
    if(this->clip_rect){
        if(!RenderManager::iscollisionRect(Rect (this->x,this->y,bgrect.width,bgrect.height), *this->clip_rect))
            return -3;
    }else{
        if(!RenderManager::isInViewportRange(this->x,this->y,bgrect.width,bgrect.height))
            return -3;
    }

    //set clipping Rect
    Rect clippedRect;

    clippedRect.x = this->x;
    clippedRect.y = this->y;
    clippedRect.width = bgrect.width;
    clippedRect.height = bgrect.height;

    //if: bgrect = normale size of Texture (or src_rect = 0)
    //Add zoom factor
    if(this->zoom_x != 1.0f && this->src_rect.width == 0)
        clippedRect.width = static_cast<GLint>(bgrect.width*this->zoom_x);

    if(this->zoom_y != 1.0f && this->src_rect.height == 0)
        clippedRect.height = static_cast<GLint>(bgrect.height*this->zoom_y);

    if(this->clip_rect){
        clippedRect.x = std::max(this->clip_rect->x,clippedRect.x);
        clippedRect.y = std::max(this->clip_rect->y,clippedRect.y);
        clippedRect.width = std::min(this->clip_rect->width,clippedRect.width);
        clippedRect.height = std::min(this->clip_rect->height,clippedRect.height);
    }

    RenderManager::enableScissor(true);
    RenderManager::setScissorInTopLeftMode(clippedRect);

    RenderManager::enable2DTexture(this->pixels != NULL);
    RenderManager::bindTexture(this->texture);
    RenderManager::setTexParam(this->filter);
    RenderManager::setBlendFunc(this->blend_type);
    RenderManager::setCoord(this->x,this->y,
                            (this->z + ((this->viewport)? this->viewport->z : 0.0f))*100.0f,
                            bgrect.width,bgrect.height,
                            this->angle_x,this->angle_y,this->angle_z,
                            this->zoom_x,this->zoom_y);

    GLint glviewport[4] = {0};
    glGetIntegerv(GL_VIEWPORT, glviewport);

    //viewport[]: glGetIntegerv(GL_VIEWPORT, viewport)
    //this->src_rect.width: width of feld
    //this->src_rect.height: height of feld
    //number of Textures to fill the field
    size_t sizex = std::max(std::min<int>(glviewport[0]+glviewport[2]-this->x,bgrect.width/this->bitmapWidth),0)+2;
    size_t sizey = std::max(std::min<int>(glviewport[1]+glviewport[3]-this->y,bgrect.height/this->bitmapHeight),0)+2;
    size_t sizefeld = sizex*sizey;

    //Array of texcoord,vertices and colors
    //texcoord[x][y] = {x,y,            width,y,
    //                  width,height,   x,height}
    //vertices[x][y] = {x,y,z,            width,y,z,
    //                  width,height,z,   x,height,z}
    //vcolors[x][y] =  {r,g,b,a,        r,g,b,a,
    //                  r,g,b,a,        r,g,b,a}
    GLdouble* texcoord = new GLdouble[sizefeld*8]();
    GLdouble* vertices = new GLdouble[sizefeld*12]();
    GLubyte* vcolors = new GLubyte[sizefeld*16]();

    //set texcoord and vertices of Textures
    if(sizex == 1 && sizey == 1){
        RenderManager::getTexCoordArray8(texcoord,srect,texW,texH);
        RenderManager::getVerticesArray12(vertices,0,0,0,srect.width,srect.height);
        if(this->flippedH){
            RenderManager::flippedHTexCoord8(texcoord);
        }
        if(this->flippedV){
            RenderManager::flippedVTexCoord8(texcoord);
        }
    }else{
        for(size_t iy = 0;iy < sizey;iy++){
            for(size_t ix = 0;ix < sizex;ix++){
                /**
                *|-----------||-----------------||-----------------|
                *| ix:0,iy0  || 1,0             || 2,0             |
                *| srect     || srect/fullsrect || srect/fullsrect |
                *|-----------||-----------------||-----------------|
                *|-----------------||-----------------||-----------------|
                *| 0,1             || 1,1             || 2,1             |
                *| srect/fullsrect || fullsrect       || fullsrect       |
                *|-----------------||-----------------||-----------------|
                *|-----------------||-----------------||-----------------|
                *| 0,2             || 1,2             || 2,2             |
                *| srect/fullsrect || fullsrect       || fullsrect       |
                *|-----------------||-----------------||-----------------|
                *
                *vertices[ix][iy] = {x,y,            width,y,
                *                    width,height,   x,height}
                */
                size_t itex = (ix+iy*sizex)*8;
                size_t ivec = (ix+iy*sizex)*12;

                RenderManager::getTexCoordArray8(&texcoord[itex],fullsrect,texW,texH);

                if(this->flippedH){
                    RenderManager::flippedHTexCoord8(&texcoord[itex]);
                }
                if(this->flippedV){
                    RenderManager::flippedVTexCoord8(&texcoord[itex]);
                }

                GLdouble vertexx = 0.0f-srect.x;
                GLdouble vertexy = 0.0f-srect.y;
                GLdouble vertexwidth = fullsrect.width;
                GLdouble vertexheight = fullsrect.height;
                if(ix > 0){
                    vertexx = 0.0f-srect.x + srect.width + fullsrect.width*(ix-1);
                }
                if(iy > 0){
                    vertexy = 0.0f-srect.y + srect.height + fullsrect.height*(iy-1);
                }
                RenderManager::getVerticesArray12(&vertices[ivec],vertexx,vertexy,0,vertexwidth,vertexheight);
            }
        }
    }

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

        //sizefeld*4 = sizefeld * Numbers of Vertex
        RenderManager::getColorArrayQuad4(vcolors,this->vColor,sizefeld,4);
        RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,sizefeld,Plane::VertexArray);

        if(isneedstencil){
            //end Stencil (Stencil is in memory)
            RenderManager::endStencil();
        }

        //rendering with tonecolor
        //use Stencil
        if(this->tone.getRed() != 0 || this->tone.getGreen() != 0 || this->tone.getBlue() != 0){
            RenderManager::enable2DTexture(false); //only color needed
            RenderManager::setBlendFunc(BlendType::additives);

            GLubyte rgb[3] = {0};
            ColorTone::ColorTonetoRGB(this->tone,rgb);
            Color newvColors[4];
            for(size_t i = 0;i < 4;++i)
                newvColors[i].set(rgb[0],rgb[1],rgb[2],this->vColor[i].alpha);

            RenderManager::getColorArrayQuad4(vcolors,this->vColor,sizefeld,4);
            RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,sizefeld,Plane::VertexArray);
        }

        //rendering with (viewport) tonecolor
        //use Stencil
        if(this->viewport){
            if(this->viewport->tone.getRed() != 0 || this->viewport->tone.getGreen() != 0 || this->viewport->tone.getBlue() != 0){
                RenderManager::enable2DTexture(false); //only color needed
                RenderManager::setBlendFunc(BlendType::additives);

                GLubyte rgb[3] = {0};
                ColorTone::ColorTonetoRGB(this->viewport->tone,rgb);
                Color newvColors[4];
                for(size_t i = 0;i < 4;++i)
                    newvColors[i].set(rgb[0],rgb[1],rgb[2],this->vColor[i].alpha);

                RenderManager::getColorArrayQuad4(vcolors,this->vColor,sizefeld,4);
                RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,sizefeld,Plane::VertexArray);
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

        RenderManager::getColorArrayQuad4(vcolors,this->vColor,sizefeld,4);

        glUseProgramObjectARB( this->ShaderProgramObj );
        RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,sizefeld,Plane::VertexArray);
        glUseProgramObjectARB( 0 );
    }

    delete[] vcolors;
    delete[] texcoord;
    delete[] vertices;

    RenderManager::enableScissor(false);
    RenderManager::enable2DTexture(false);

    return 1;
}
}
