#include <Fantasy2C/Plane.hpp>

namespace F2C{

GLhandleARB Plane::ShaderProgramObj = 0;
TexParam::Tex_Param Plane::filter = TexParam::Linear;
bool Plane::VertexArray = false;
bool Plane::checkVertexArray = false;

Plane::Plane(const Plane& copy):
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Plane::checkVertexArray){
        Plane::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        Plane::checkVertexArray = true;
    }

	*this = copy;
}

Plane& Plane::operator= (const Plane& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;

        this->SpriteBase::operator = (copy);
    }
    return *this;
}

Plane::Plane():
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Plane::checkVertexArray){
        Plane::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        Plane::checkVertexArray = true;
    }
}

Plane::Plane(const Bitmap* bitmap):
    SpriteBase(bitmap),
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Plane::checkVertexArray){
        Plane::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        Plane::checkVertexArray = true;
    }
}

Plane::Plane(Viewport* viewport):
    clip_rect(NULL),
	viewport(viewport)
{
    if(!Plane::checkVertexArray){
        Plane::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        Plane::checkVertexArray = true;
    }

   if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
       this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 )
         this->clip_rect = &this->viewport->clip_rect;

}

int Plane::render() const{
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

    //Size of Background
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
        GLint left1, left2;
        GLint right1, right2;
        GLint top1, top2;
        GLint bottom1, bottom2;

        left1 = this->x;
        left2 = this->clip_rect->x;
        right1 = this->x + bgrect.width;
        right2 = this->clip_rect->x + this->clip_rect->width;
        top1 = this->y;
        top2 = this->clip_rect->y;
        bottom1 = this->y + bgrect.height;
        bottom2 = this->clip_rect->y + this->clip_rect->height;

        if((bottom1 < top2) || (top1 > bottom2) || (right1 < left2) ||
            (left1 > right2))
                return -3;
    }else{
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        GLint left1, left2;
        GLint right1, right2;
        GLint top1, top2;
        GLint bottom1, bottom2;

        left1 = this->x;
        left2 = viewport[0];
        right1 = this->x + bgrect.width;
        right2 = viewport[0] + viewport[2];
        top1 = this->y;
        top2 = viewport[1];
        bottom1 = this->y + bgrect.height;
        bottom2 = viewport[1] + viewport[3];

        if((bottom1 < top2) || (top1 > bottom2) || (right1 < left2) ||
            (left1 > right2))
                return -3;
    }

    //set clipping Rect
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLint clippedLeft = this->x;
    GLint clippedTop = this->y;
    GLint clippedRight = this->x;
    GLint clippedBottom = this->y;

    //if: bgrect = normale size of Texture (or src_rect = 0)
    //Add zoom factor
    if(this->zoom_x != 1.0f && this->src_rect.width == 0)
        clippedRight += static_cast<GLint>(bgrect.width*this->zoom_x);
    else
        clippedRight += bgrect.width;

    if(this->zoom_y != 1.0f && this->src_rect.height == 0)
        clippedBottom += static_cast<GLint>(bgrect.height*this->zoom_y);
    else
        clippedBottom += bgrect.height;

    if(this->clip_rect){
        clippedLeft = std::max<int>(this->clip_rect->x,clippedLeft);
        clippedTop = std::max<int>(this->clip_rect->y,clippedTop);
        clippedRight = std::min<uint>(this->clip_rect->x + this->clip_rect->width,clippedRight);
        clippedBottom = std::min<uint>(this->clip_rect->y + this->clip_rect->height,clippedBottom);
    }

    // translate from top left to bottom left coordinate system
    glScissor(clippedLeft, viewport[3] - clippedBottom, clippedRight - clippedLeft, clippedBottom);

    int active_texture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D,&active_texture);
    if(static_cast<uint>(active_texture) != this->texture){
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }

    if(this->filter == TexParam::Nearest){
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    }else if(this->filter == TexParam::Linear){
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLdouble invW = 1.0f / texW;
    GLdouble invH = 1.0f / texH;

    //set texcoord of first Texture
    //texcoord: top
    GLdouble cx = srect.x * invW;

    //texcoord: left
    GLdouble cy = srect.y * invH;

    //texcoord: right
    GLdouble cwidth = (srect.width+srect.x) * invW;

    //texcoord: bottom
    GLdouble cheight = (srect.height+srect.y) * invH;

    cx = (cx > cwidth)? cwidth : cx;
    cy = (cy > cheight)? cheight : cy;

    //vertex: right
    GLdouble vwidth = srect.width;

    //vertex: bottom
    GLdouble vheight = srect.height;

    //set texcoord of full Texture
    //texcoord: top
    GLdouble fullcx = fullsrect.x * invW;

    //texcoord: left
    GLdouble fullcy = fullsrect.y * invH;

    //texcoord: right
    GLdouble fullcwidth = (fullsrect.width+fullsrect.x) * invW;

    //texcoord: bottom
    GLdouble fullcheight = (fullsrect.height+fullsrect.y) * invH;

    fullcx = (fullcx > fullcwidth)? fullcwidth : fullcx;
    fullcy = (fullcy > fullcheight)? fullcheight : fullcy;

    //vertex: right
    GLdouble fullvwidth = fullsrect.width;

    //vertex: bottom
    GLdouble fullvheight = fullsrect.height;

    glEnable(GL_SCISSOR_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);

    glLoadIdentity();
    //move to middle
    glTranslated(this->x+(bgrect.width/2.0f),
                  this->y+(bgrect.height/2.0f),
                  (this->z + ((this->viewport)? this->viewport->z : 0)) * 100.0f);
    //rotate in the middle
    glRotated(this->angle_x,1.0f,0.0f,0.0f);
    glRotated(this->angle_y,0.0f,1.0f,0.0f);
    glRotated(this->angle_z,0.0f,0.0f,1.0f);
    //move back
    glTranslated(bgrect.width/-2.0f,
                  bgrect.height/-2.0f,
                  0.0f);
    glScaled(this->zoom_x,this->zoom_y,1.0f);

    //viewport[]: glGetIntegerv(GL_VIEWPORT, viewport)
    //this->src_rect.width: width of feld
    //this->src_rect.height: height of feld
    //number of Textures to fill the field
    size_t sizex = std::max<size_t>(static_cast<size_t>(std::min<double>(viewport[0]+viewport[2]-this->x,bgrect.width)/static_cast<double>(this->bitmapWidth)),1)+2;
    size_t sizey = std::max<size_t>(static_cast<size_t>(std::min<double>(viewport[1]+viewport[3]-this->y,bgrect.height)/static_cast<double>(this->bitmapHeight)),1)+2;

    //3D-Array of texcoord,vertices and colors
    //texcoord[x][y] = {x,y,            width,y,
    //                  width,height,   x,height}
    //vertices[x][y] = {x,y,z,            width,y,z,
    //                  width,height,z,   x,height,z}
    //vcolors[x][y] =  {r,g,b,a,        r,g,b,a,
    //                  r,g,b,a,        r,g,b,a}
    GLdouble* texcoord = new GLdouble[sizex*sizey*8]();
    GLdouble* vertices = new GLdouble[sizex*sizey*12]();
    GLubyte* vcolors = new GLubyte[sizex*sizey*16]();

    //set texcoord and vertices of Textures
    if(sizex == 1 && sizey == 1){
        texcoord[0] = cx;
        texcoord[1] = cy;
        texcoord[2] = cwidth;
        texcoord[3] = cy;
        texcoord[4] = cwidth;
        texcoord[5] = cheight;
        texcoord[6] = cx;
        texcoord[7] = cheight;

        vertices[0] = 0.0f;
        vertices[1] = 0.0f;
        vertices[2] = 0.0f;

        vertices[3] = vwidth;
        vertices[4] = 0.0f;
        vertices[5] = 0.0f;

        vertices[6] = vwidth;
        vertices[7] = vheight;
        vertices[8] = 0.0f;

        vertices[9] = 0.0f;
        vertices[10] = vheight;
        vertices[11] = 0.0f;

        if(this->flippedH){
            std::swap(texcoord[0],texcoord[2]);
            std::swap(texcoord[4],texcoord[6]);
        }
        if(this->flippedV){
            std::swap(texcoord[1],texcoord[7]);
            std::swap(texcoord[3],texcoord[5]);
        }
    }else{
        for(size_t iy = 0;iy < sizey;iy++){
            for(size_t ix = 0;ix < sizex;ix++){
                /**
                *|-----------||-----------------||-----------------|
                *| ix:0,iy0  || 1,0             || 2,0             |
                *| srect     || fullsrect       || fullsrect       |
                *|-----------||-----------------||-----------------|
                *|-----------------||-----------------||-----------------|
                *| 0,1             || 1,1             || 2,1             |
                *| fullsrect       || fullsrect       || fullsrect       |
                *|-----------------||-----------------||-----------------|
                *
                *vertices[ix][iy] = {x,y,            width,y,
                *                    width,height,   x,height}
                */
                size_t coorditex = (ix+iy*sizex)*8;
                size_t coordivec = (ix+iy*sizex)*12;

//                texcoord[coorditex] = (ix > 0)? fullcx : cx;
//                texcoord[1+coorditex] = (iy > 0)? fullcy : cy;
//                texcoord[2+coorditex] = (ix > 0)? fullcwidth : cwidth;
//                texcoord[3+coorditex] = (iy > 0)? fullcy : cy;
//                texcoord[4+coorditex] = (ix > 0)? fullcwidth : cwidth;
//                texcoord[5+coorditex] = (iy > 0)? fullcheight : cheight;
//                texcoord[6+coorditex] = (ix > 0)? fullcx : cx;
//                texcoord[7+coorditex] = (iy > 0)? fullcheight : cheight;
//
//                vertices[coordivec] = (ix > 0)? vwidth+fullvwidth*(ix-1) : 0.0f;
//                vertices[1+coordivec] = (iy > 0)? vheight+fullvheight*(iy-1) : 0.0f;
//                vertices[2+coordivec] = 0.0f;
//
//                vertices[3+coordivec] = (ix > 0)? vwidth+fullvwidth*(ix) : vwidth;
//                vertices[4+coordivec] = (iy > 0)? vheight+fullvheight*(iy-1) : 0.0f;
//                vertices[5+coordivec] = 0.0f;
//
//                vertices[6+coordivec] = (ix > 0)? vwidth+fullvwidth*(ix) : vwidth;
//                vertices[7+coordivec] = (iy > 0)? vheight+fullvheight*(iy) : vheight;
//                vertices[8+coordivec] = 0.0f;
//
//                vertices[9+coordivec] = (ix > 0)? vwidth+fullvwidth*(ix-1) : 0.0f;
//                vertices[10+coordivec] = (iy > 0)? vheight+fullvheight*(iy) : vheight;
//                vertices[11+coordivec] = 0.0f;

                texcoord[coorditex] = fullcx;
                texcoord[1+coorditex] = fullcy;
                texcoord[2+coorditex] = fullcwidth;
                texcoord[3+coorditex] = fullcy;
                texcoord[4+coorditex] = fullcwidth;
                texcoord[5+coorditex] = fullcheight;
                texcoord[6+coorditex] = fullcx;
                texcoord[7+coorditex] = fullcheight;

                vertices[coordivec] = (ix > 0)? vwidth+fullvwidth*(ix-1)-srect.x : 0.0f-srect.x;
                vertices[1+coordivec] = (iy > 0)? vheight+fullvheight*(iy-1)-srect.y : 0.0f-srect.y;
                vertices[2+coordivec] = 0.0f;

                vertices[3+coordivec] = (ix > 0)? vwidth+fullvwidth*(ix)-srect.x : vwidth-srect.x;
                vertices[4+coordivec] = (iy > 0)? vheight+fullvheight*(iy-1)-srect.y : 0.0f-srect.y;
                vertices[5+coordivec] = 0.0f;

                vertices[6+coordivec] = (ix > 0)? vwidth+fullvwidth*(ix)-srect.x : vwidth-srect.x;
                vertices[7+coordivec] = (iy > 0)? vheight+fullvheight*(iy)-srect.y : vheight-srect.y;
                vertices[8+coordivec] = 0.0f;

                vertices[9+coordivec] = (ix > 0)? vwidth+fullvwidth*(ix-1)-srect.x : 0.0f-srect.x;
                vertices[10+coordivec] = (iy > 0)? vheight+fullvheight*(iy)-srect.y : vheight-srect.y;
                vertices[11+coordivec] = 0.0f;

                if(this->flippedH){
                    std::swap(texcoord[coorditex],texcoord[2+coorditex]);
                    std::swap(texcoord[4+coorditex],texcoord[6+coorditex]);
                }
                if(this->flippedV){
                    std::swap(texcoord[1+coorditex],texcoord[7+coorditex]);
                    std::swap(texcoord[3+coorditex],texcoord[5+coorditex]);
                }
            }
        }
    }

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glTexCoordPointer(2, GL_DOUBLE, 0, texcoord);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);

    /**
    *Rendering
    * r =
    * 0: Fill Stencil Buffer and normal Texture rendering
    * 1: Rect with this->tone Color rendering
    * 2; Rect with this->viewport->tone Color rendering
    * 3: grayscale Texture rendering
    */
    bool needstencil = (this->tone.grayscale < 255 || !this->ShaderProgramObj) &&
                        (this->tone.getRed() != 0 || this->tone.getGreen() != 0 || this->tone.getBlue() != 0);
    if(this->viewport)
        needstencil |= (this->tone.grayscale < 255 || !this->ShaderProgramObj) &&
                        (this->viewport->tone.getRed() != 0 || this->viewport->tone.getGreen() != 0 || this->viewport->tone.getBlue() != 0);
    for(size_t r = 0;r < 4;r++){
        //check if need rendering
        //if: normal Texture rendering
        if((this->tone.grayscale < 255 || !this->ShaderProgramObj) && r != 3){
            //if not: normal texture rendering
            if(r == 0 && !(this->tone.grayscale < 255 || !this->ShaderProgramObj))
                continue;
            //if not: this->tone Colors != 0
            else if(r == 1 && !(this->tone.getRed() != 0 || this->tone.getGreen() != 0 || this->tone.getBlue() != 0))
                continue;
            //if not: viewport exists
            else if(r == 2 && !this->viewport)
                continue;
            //if not: this->viewport->tone Colors != 0
            else if(r == 2 && this->viewport){
                if(!(this->viewport->tone.getRed() != 0 || this->viewport->tone.getGreen() != 0 || this->viewport->tone.getBlue() != 0))
                    continue;
            }
        }
        //if not: grayscale Texture rendering
        else if(r == 3 && !(this->ShaderProgramObj && this->tone.grayscale > 0))
            continue;

        //set vColor,tone or grayscale Color
        for(size_t iy = 0;iy < sizey;iy++){
            for(size_t ix = 0;ix < sizex;ix++){
                for(size_t i = 0;i < 4;i++){
                    GLubyte rgb[3] = {0,0,0};
                    switch(r){
                        case 0:
                            vcolors[(i+(ix+iy*sizex)*4)*4] = this->vColor[i].red;
                            vcolors[1+(i+(ix+iy*sizex)*4)*4] = this->vColor[i].green;
                            vcolors[2+(i+(ix+iy*sizex)*4)*4] = this->vColor[i].blue;
                        break;
                        case 1:
							ColorTone::ColorTonetoRGB(this->tone,rgb);
                            vcolors[(i+(ix+iy*sizex)*4)*4] = rgb[0];
                            vcolors[1+(i+(ix+iy*sizex)*4)*4] = rgb[1];
                            vcolors[2+(i+(ix+iy*sizex)*4)*4] = rgb[2];
                        break;
                        case 2:
                            if(this->viewport){
                                ColorTone::ColorTonetoRGB(this->viewport->tone,rgb);
                                vcolors[i*4] = rgb[0];
                                vcolors[1+i*4] = rgb[1];
                                vcolors[2+i*4] = rgb[2];
                            }
                        break;
                        default:
                            vcolors[(i+(ix+iy*sizex)*4)*4] = 255;
                            vcolors[1+(i+(ix+iy*sizex)*4)*4] = 255;
                            vcolors[2+(i+(ix+iy*sizex)*4)*4] = 255;
                    }
                    if(r == 3)
                        vcolors[3+(i+(ix+iy*sizex)*4)*4] = std::min<uint8>(this->vColor[i].alpha,this->tone.grayscale);
                    else
                        vcolors[3+(i+(ix+iy*sizex)*4)*4] = this->vColor[i].alpha;
                }
            }
        }

        //if: Bitmap exists and need Texture rendering
        //(r1 and r2 are Rects without Textures)
        if((this->bitmapWidth > 0 || this->bitmapHeight > 0) && (r == 0 || r == 3 ))
            glEnable(GL_TEXTURE_2D);
        else
            glDisable(GL_TEXTURE_2D);

        //additive blending for tone Color effect
        //or blending for normal Texture
        if(r == 1 || r == 2){
            glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        }else{
            if(this->blend_type == BlendType::additives)
                glBlendFunc(GL_SRC_ALPHA,GL_ONE);
            else if(this->blend_type == BlendType::normal)
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            else if(this->blend_type == BlendType::multiplicative)
                glBlendFunc(GL_DST_COLOR,GL_ZERO);
        }

        if(needstencil){
            if((r == 0 || r == 1 || r == 2)){
                glEnable(GL_STENCIL_TEST);
            }else{
                glDisable(GL_STENCIL_TEST);
            }
            if(r == 0){
                glClear(GL_STENCIL_BUFFER_BIT);
                glStencilFunc(GL_ALWAYS,1,1);
                glStencilOp(GL_KEEP, GL_INVERT , GL_INVERT);
            }else{
                glStencilFunc(GL_EQUAL, 1, 1);
                glStencilOp(GL_KEEP,GL_KEEP, GL_KEEP);
            }
        }

        //grayscale rendering need Shader Program
        if(r == 3)
            glUseProgramObjectARB( this->ShaderProgramObj );

        if(Plane::VertexArray){
            glColorPointer(4,GL_UNSIGNED_BYTE, 0, vcolors);
            glDrawArrays(GL_QUADS, 0, sizex*sizey*4);
        }else{
            uint i = 0;
            uint j = 0;
            uint k = 0;
            glBegin(GL_QUADS);
            for(;i < sizex*sizey*8 || j < sizex*sizey*12 || k < sizex*sizey*16;i+=2,j+=3,k+=4){
                glColor4ubv(&vcolors[k]);
                glTexCoord2dv(&texcoord[i]);
                glVertex3dv(&vertices[j]);
            }
            glEnd();
        }

        if(r == 3)
            glUseProgramObjectARB(0);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    delete[] vcolors;
    delete[] texcoord;
    delete[] vertices;

    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);

    return 1;
}

void Plane::copyProperties(const Plane& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;

        this->SpriteBase::copyProperties(copy);
    }
}

void Plane::setViewport(Viewport* viewport){
    this->viewport = viewport;
    if(!this->viewport){
        this->clip_rect = NULL;
        return;
    }

    if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
                this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 ){
                    this->clip_rect = &this->viewport->clip_rect;
    }
}


};

