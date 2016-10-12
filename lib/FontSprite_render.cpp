#include <Fantasy2C/FontSprite.hpp>

namespace F2C{

int16 FontSprite::render() const{
    //if: no Rexts to render
    if (this->strings.empty() || this->rect_strings.empty())
        return -3;

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

    //width and height of Texture
    GLdouble texW = this->pixelsWidth;
    GLdouble texH = this->pixelsWidth;

    if(texW == 0 || texH == 0)
        return -2;

    RenderManager::enableScissor(true);
    RenderManager::enable2DTexture(this->pixels != NULL);
    RenderManager::bindTexture(this->texture);
    RenderManager::setTexParam(this->filter);
    RenderManager::setBlendFunc(this->blend_type);

    //for: Texts
    for(size_t i = 0;i < this->strings.size();++i){
        //column coord.
        GLdouble ccx = 0.0f;

        //line coord.
        GLdouble ccy = 0.0f;

        //text coord.
        Rect strrect = this->rect_strings[i];
        strrect.x = this->x+this->rect_strings[i].x;
        strrect.y = this->y+this->rect_strings[i].y;

        //if: Text outside of clipping Rect or Display
        if(this->clip_rect){
            if(!RenderManager::iscollisionRect(strrect, *this->clip_rect))
                continue;
        }else{
            if(!RenderManager::isInViewportRange(strrect))
                continue;
        }

        RenderManager::setCoord(strrect.x,strrect.y,
                                (this->z + ((this->viewport)? this->viewport->z : 0.0f))*100.0f,
                                0,0,
                                this->angle_x,this->angle_y,this->angle_z,
                                this->zoom_x,this->zoom_y);

        //set src_rect(clipping rect) of Texts
        Rect clippedRect = strrect;

        if(this->src_rect.width > 0 && this->src_rect.height > 0){
            clippedRect.x = std::max(this->x+this->src_rect.x,clippedRect.x);
            clippedRect.y = std::max(this->y+this->src_rect.y,clippedRect.y);
            clippedRect.width = std::min(this->src_rect.width,clippedRect.width);
            clippedRect.height = std::min(this->src_rect.height,clippedRect.height);
        }
        if(this->clip_rect){
            clippedRect.x = std::max(this->clip_rect->x,clippedRect.x);
            clippedRect.y = std::max(this->clip_rect->y,clippedRect.y);
            clippedRect.width = std::min(this->clip_rect->width,clippedRect.width);
            clippedRect.height = std::min(this->clip_rect->height,clippedRect.height);
        }

        RenderManager::setScissorInTopLeftMode(clippedRect);

        //Array of texcoord,vertices and colors
        //texcoord[letter] = {x,y,            width,y,
        //                    width,height,   x,height}
        //vertices[letter] = {x,y,z,            width,y,z,
        //                    width,height,z,   x,height,z}
        //vcolors[letter] =  {r,g,b,a,        r,g,b,a,
        //                    r,g,b,a,        r,g,b,a}
        GLdouble* texcoord = new GLdouble[this->strings[i].length()*8]();
        GLdouble* vertices = new GLdouble[this->strings[i].length()*12]();
        GLubyte* vcolors = new GLubyte[this->strings[i].length()*16]();

        size_t strlength = this->strings[i].length();
        std::string str = this->strings[i];

        //for: set texcoords and vertices of all letters
        for(size_t j = 0;j < strlength;j++){
            size_t cid = static_cast<size_t>(str[j]);
            uint charw = this->char_rect[cid].width;
            uint charh = this->char_rect[cid].height;

            RenderManager::getTexCoordArray8(&texcoord[j*8],this->char_rect[cid],texW,texH);
            RenderManager::getVerticesArray12(&vertices[j*12],ccx,ccy,0,charw,charh);

            //set italic letter
            if(this->italic){
                //upper-left vertex
                vertices[j*12] += charw*0.125f;
                //upper-right vertex
                vertices[3+j*12] += charw*0.125f;
            }

            if(this->flippedH){
                RenderManager::flippedHTexCoord8(&texcoord[j*8]);
            }
            if(this->flippedV){
                RenderManager::flippedVTexCoord8(&texcoord[j*8]);
            }

            ccx += charw;

            if(str[j] == '\n'){
                ccy += this->char_rect[cid].height;
                ccx = 0.0f;
            }
        }

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

            RenderManager::getColorArrayQuad4(vcolors,this->vColor,strlength,4);
            RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,strlength,FontSprite::VertexArray);

            if(isneedstencil){
                //end Stencil (Stencil is in memory)
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

                RenderManager::getColorArrayQuad4(vcolors,newvColors,strlength,4);
                RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,strlength,FontSprite::VertexArray);
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

                    RenderManager::getColorArrayQuad4(vcolors,newvColors,strlength,4);
                    RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,strlength,FontSprite::VertexArray);
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

            RenderManager::getColorArrayQuad4(vcolors,newvColors,strlength,4);

            glUseProgramObjectARB( this->ShaderProgramObj );
            RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,strlength,FontSprite::VertexArray);
            glUseProgramObjectARB( 0 );
        }

        delete[] texcoord;
        delete[] vertices;
        delete[] vcolors;
    }

    RenderManager::enableScissor(false);
    RenderManager::enable2DTexture(false);

    return 1;
}

}
