#include <Fantasy2C/ArraySprite.hpp>

namespace F2C{

    int16 ArraySprite::render() const{
        if(this->elements.empty())
            return -4;
        return this->render(0,this->elements.size());
    }

    int16 ArraySprite::render(size_t starteid) const{
        if(this->elements.empty())
            return -4;
        return this->render(starteid,this->elements.size());
    }

    int16 ArraySprite::render(size_t starteid,size_t endeid) const{
        //if: array empty
        if(this->elements.empty())
            return -4;

        //out of array rang
        endeid = std::min(endeid,this->elements.size());
        if(starteid > endeid)
            return -5;

        //if: show == false
        if (this->viewport){
          if(!viewport->show)
             return -1;
        }

        //if: Zoom-Factor == 0
        if(this->zoom_x == 0.0f || this->zoom_y == 0.0f)
            return -3;

        //width of Texture
        GLdouble texW = 0.0f;

        //height of Texture
        GLdouble texH = 0.0f;

        //set Texture Size: Bitmap or simple Rect(with this->src_rect)
        if(this->bitmapWidth > 0 || this->bitmapHeight > 0){
            texW = this->pixelsWidth;
            texH = this->pixelsWidth;
        }
        if(texW == 0 || texH == 0)
            return -2;

        size_t esize = std::min<size_t>(std::max<int>(endeid-starteid,1),this->elements.size());
        if(esize == 0)
            return -5;

        //2D-Array of texcoord,vertices and vcolors
        //texcoord[element] = {x,y,            width,y,
        //					   width,height,   x,height}
        //vertices[element] = {x,y,z,            width,y,z,
        //					   width,height,z,   x,height,z}
        //vcolors[element] =  {r,g,b,a,        r,g,b,a,
        //					   r,g,b,a,        r,g,b,a}
        GLdouble* texcoord = new GLdouble[esize*8]();
        GLdouble* vertices = new GLdouble[esize*12]();
        GLubyte* vcolors = new GLubyte[esize*16]();

        size_t e = 0;
        for(std::vector<SpriteElement>::const_iterator element = this->elements.begin()+starteid; element < this->elements.begin()+endeid; element++,e++){
            //if: show == false
    //		if(!element->show)
    //			continue;
    //
    //		//if: Alpha Color == 0
    //		if(element->vColor[0].alpha < 1 &&
    //			element->vColor[1].alpha < 1 &&
    //			element->vColor[2].alpha < 1 &&
    //			element->vColor[3].alpha < 1){
    //				continue;
    //		}
    //
    //		//if: Zoom-Factor == 0
    //		if(element->zoom_x == 0.0f || element->zoom_y == 0.0f)
    //			continue;

            //source Rect of Texture
            Rect srect = element->src_rect;

            //set Texture Size: Bitmap or simple Rect(with this->src_rect)
            if(this->bitmapWidth > 0 || this->bitmapHeight > 0){
                if (srect.width == 0)
                    srect.width = this->bitmapWidth;
                if (srect.height == 0)
                    srect.height = this->bitmapHeight;
                texW = this->pixelsWidth;
                texH = this->pixelsWidth;
            }else{
                texW = element->src_rect.width;
                texH = element->src_rect.height;
            }
    //        if(texW == 0 || texH == 0)
    //            continue;

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
    //		if(this->clip_rect){
    //            if(!RenderManager::iscollisionRect(Rect (this->x+element->x,this->y+element->y,srect.width,srect.height), *this->clip_rect))
    //                continue;
    //        }else{
    //            if(!RenderManager::isInViewportRange(this->x+element->x,this->y+element->y,srect.width,srect.height))
    //                continue;
    //        }

            RenderManager::getTexCoordArray8(&texcoord[e*8],srect,texW,texH);
            if(element->flippedH){
                RenderManager::flippedHTexCoord8(&texcoord[e*8]);
            }
            if(element->flippedV){
                RenderManager::flippedVTexCoord8(&texcoord[e*8]);
            }

            RenderManager::getVerticesArray12(&vertices[e*12],
                                                element->x,element->y,element->z*100.0f,
                                                srect.width*element->zoom_x,
                                                srect.height*element->zoom_y);

            if(element->angle_z != 0.0f){
                GLdouble angle = element->angle_z * (M_PI / 180.0f); //convert Grad in Rad(1 Rad = PI/180)
                GLdouble sine = sin(angle);
                GLdouble cose = cos(angle);
                /**
                * i:
                * (00,01,02)--------(03,04,05)
                *      |                 |
                *      |                 |
                * (09,10,11)--------(06,07,08)
                */
                for (size_t i = 0;i < 12;i+=3){
                    //move to middle
                    //GLfloat addvx = ((i == 3 || i == 6)? (vwidth/-2.0f)  : (vwidth/2.0f) );
                    //GLfloat addvy = ((i == 6 || i == 9)? (vheight/-2.0f) : (vheight/2.0f) );

                    /**
                    *Rotation Z
                    *move to zero point and center
                    * sX = XW - X +- W/2
                    * sY = YH - X +- H/2
                    * X = (sX * Cos(Rad)) - (sY * Sin(Rad))
                    * Y = (sY * Sin(Rad)) + (sY * Cos(Rad))
                    */
                    GLdouble newvx = ((vertices[i+e*12]-vertices[0+e*12]) * cose) - ((vertices[(i+1)+e*12]-vertices[1+e*12]) * sine);
                    GLdouble newvy = ((vertices[i+e*12]-vertices[0+e*12]) * sine) + ((vertices[(i+1)+e*12]-vertices[1+e*12]) * cose);

                    //GLfloat cvx = ((addvx) * cose) - ((addvy) * sine);
                    //GLfloat cvy = ((addvx) * sine) + ((addvy) * cose);

                    //move back (remove zero point and center)
                    vertices[i+e*12] = newvx + vertices[0+e*12];
                    vertices[(i+1)+e*12] = newvy + vertices[1+e*12];
                }
            }
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
                                0,0,0,0,0,
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

            e = 0;
            for(std::vector<SpriteElement>::const_iterator element = this->elements.begin()+starteid; element < this->elements.begin()+endeid; element++,e++){
                RenderManager::getColorArray4(&vcolors[e*16],element->vColor,4,4);
            }
            RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,esize,ArraySprite::VertexArray);

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

                e = 0;
                for(std::vector<SpriteElement>::const_iterator element = this->elements.begin()+starteid; element < this->elements.begin()+endeid; element++,e++){
                    for(size_t i = 0;i < 4;++i){
                        newvColors[i].set(rgb[0],rgb[1],rgb[2],element->vColor[i].alpha);
                    }
                    RenderManager::getColorArray4(&vcolors[e*16],newvColors,4,4);
                }

                RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,esize,ArraySprite::VertexArray);
            }

            //rendering with (viewport) tonecolor
            if(this->viewport){
                if(this->viewport->tone.getRed() != 0 || this->viewport->tone.getGreen() != 0 || this->viewport->tone.getBlue() != 0){
                    RenderManager::enable2DTexture(false); //only color needed
                    RenderManager::setBlendFunc(BlendType::additives);

                    GLubyte rgb[3] = {0};
                    ColorTone::ColorTonetoRGB(this->viewport->tone,rgb);
                    Color newvColors[4];

                    e = 0;
                    for(std::vector<SpriteElement>::const_iterator element = this->elements.begin()+starteid; element < this->elements.begin()+endeid; element++,e++){
                        for(size_t i = 0;i < 4;++i){
                            newvColors[i].set(rgb[0],rgb[1],rgb[2],element->vColor[i].alpha);
                        }
                        RenderManager::getColorArray4(&vcolors[e*16],newvColors,4,4);
                    }

                    RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,esize,ArraySprite::VertexArray);
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

            e = 0;
            for(std::vector<SpriteElement>::const_iterator element = this->elements.begin()+starteid; element < this->elements.begin()+endeid; element++,e++){
                for(size_t i = 0;i < 4;++i){
                    newvColors[i].set(255,255,255,std::min<GLubyte>(element->vColor[i].alpha,this->tone.grayscale));
                }
                RenderManager::getColorArray4(&vcolors[e*16],newvColors,4,4);
            }

            glUseProgramObjectARB( this->ShaderProgramObj );
            RenderManager::renderingQuad(texcoord,vertices,vcolors,2,3,4,esize,ArraySprite::VertexArray);
            glUseProgramObjectARB( 0 );
        }

        delete[] vcolors;
        delete[] texcoord;
        delete[] vertices;

        if(this->clip_rect)
            RenderManager::enableScissor(false);
        RenderManager::enable2DTexture(false);

        return 1;
    }
}
