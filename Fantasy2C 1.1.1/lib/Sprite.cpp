#include <Fantasy2C/Sprite.hpp>

namespace F2C{

GLhandleARB Sprite::ShaderProgramObj = 0;
TexParam::Tex_Param Sprite::filter = TexParam::Linear;
bool Sprite::VertexArray = false;
bool Sprite::checkVertexArray = false;

Sprite::Sprite(const Sprite& copy):
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Sprite::checkVertexArray){
        Sprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        Sprite::checkVertexArray = true;
    }

	*this = copy;
}

Sprite& Sprite::operator= (const Sprite& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;

        this->SpriteBase::operator = (copy);
    }
    return *this;
}

Sprite::Sprite():
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Sprite::checkVertexArray){
        Sprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        Sprite::checkVertexArray = true;
    }
}

Sprite::Sprite(const Bitmap* bitmap):
    SpriteBase(bitmap),
    clip_rect(NULL),
	viewport(NULL)
{
    if(!Sprite::checkVertexArray){
        Sprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        Sprite::checkVertexArray = true;
    }
}

Sprite::Sprite(Viewport* viewport):
    clip_rect(NULL),
	viewport(viewport)
{
    if(!Sprite::checkVertexArray){
        Sprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        Sprite::checkVertexArray = true;
    }

   if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
       this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 )
         this->clip_rect = &this->viewport->clip_rect;

}

int Sprite::render() const{
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
        int left1, left2;
        int right1, right2;
        int top1, top2;
        int bottom1, bottom2;

        left1 = this->x;
        left2 = this->clip_rect->x;
        right1 = this->x + srect.width;
        right2 = this->clip_rect->x + this->clip_rect->width;
        top1 = this->y;
        top2 = this->clip_rect->y;
        bottom1 = this->y + srect.height;
        bottom2 = this->clip_rect->y + this->clip_rect->height;

        if((bottom1 < top2) || (top1 > bottom2) || (right1 < left2) ||
            (left1 > right2))
                return -3;
    }else{
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        int left1, left2;
        int right1, right2;
        int top1, top2;
        int bottom1, bottom2;

        left1 = this->x;
        left2 = viewport[0];
        right1 = this->x + srect.width;
        right2 = viewport[0] + viewport[2];
        top1 = this->y;
        top2 = viewport[1];
        bottom1 = this->y + srect.height;
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
    GLint clippedRight = this->x+srect.width;
    GLint clippedBottom = this->y+srect.height;

    if(this->clip_rect){
        clippedLeft = std::max<int>(this->clip_rect->x,clippedLeft);
        clippedTop = std::max<int>(this->clip_rect->y,clippedTop);
        clippedRight = std::min<uint>(this->clip_rect->x + this->clip_rect->width,clippedRight);
        clippedBottom = std::min<uint>(this->clip_rect->y + this->clip_rect->height,clippedBottom);

        // translate from top left to bottom left coordinate system
        glScissor(clippedLeft, viewport[3] - clippedBottom, clippedRight - clippedLeft, clippedBottom);
    }

    int active_texture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D,&active_texture);
    if(static_cast<uint>(active_texture) != this->texture){
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }
    if(this->bitmapWidth < 1 || this->bitmapHeight < 1){
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if(this->filter == TexParam::Nearest){
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    }else if(this->filter == TexParam::Linear){
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    GLdouble invW = 1.0f / static_cast<GLfloat>(texW);
    GLdouble invH = 1.0f / static_cast<GLfloat>(texH);

    //set texcoord of Texture
    //texcoord: top
    GLdouble cx = static_cast<GLdouble>(srect.x * invW);

    //texcoord: left
    GLdouble cy = static_cast<GLdouble>(srect.y * invH);

    //texcoord: right
    GLdouble cwidth = static_cast<GLdouble>((srect.width+srect.x) * invW);

    //texcoord: bottom
    GLdouble cheight = static_cast<GLdouble>((srect.height+srect.y) * invH);

    cx = (cx > cwidth)? cwidth : cx;
    cy = (cy > cheight)? cheight : cy;

    //vertex: right
    GLdouble vwidth = static_cast<GLdouble>((srect.width));

    //vertex: bottom
    GLdouble vheight = static_cast<GLdouble>((srect.height));

    glLoadIdentity();
    //move to middle
    glTranslated(this->x+(static_cast<double>(srect.width)/2.0f),
                  this->y+(static_cast<double>(srect.height)/2.0f),
                  (this->z + ((this->viewport)? this->viewport->z : 0))*100.0f);
    //rotate in the middle
    glRotated(this->angle_x,1.0f,0.0f,0.0f);
    glRotated(this->angle_y,0.0f,1.0f,0.0f);
    glRotated(this->angle_z,0.0f,0.0f,1.0f);
    //move back
    glTranslated(srect.width/-2.0f,
                  srect.height/-2.0f,
                  0.0f);
    glScaled(this->zoom_x,this->zoom_y,1.0f);
    //Array of texcoord,vertices and colors
    //texcoord = {x,y,            width,y,
    //            width,height,   x,height}
    //vertices = {x,y,z,            width,y,z,
    //            width,height,z,   x,height,z}
    //vcolors =  {r,g,b,a,        r,g,b,a,
    //            r,g,b,a,        r,g,b,a}
    GLdouble texcoord[8] = {cx,cy,           cwidth,cy,
                           cwidth,cheight,   cx,cheight};

    GLdouble vertices[12] = {0.0f,0.0f,0.0f,        vwidth,0.0f,0.0f,
                           vwidth,vheight,0.0f,    0.0f,vheight,0.0f,};
    GLubyte vcolors[16] = {0,0,0,0,  0,0,0,0,
                           0,0,0,0,  0,0,0,0};

    if(this->flippedH){
        std::swap(texcoord[0],texcoord[2]);
        std::swap(texcoord[4],texcoord[6]);
    }
    if(this->flippedV){
        std::swap(texcoord[1],texcoord[7]);
        std::swap(texcoord[3],texcoord[5]);
    }

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    if(this->clip_rect)
        glEnable(GL_SCISSOR_TEST);
    else
        glDisable(GL_SCISSOR_TEST);

    glEnable(GL_STENCIL_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);

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

    //if: need stencil for r1 or r2
    bool needstencil = (this->tone.grayscale < 255 || !this->ShaderProgramObj) &&
                        (this->tone.getRed() != 0 || this->tone.getGreen() != 0 || this->tone.getBlue() != 0);
    if(this->viewport)
        needstencil |= (this->tone.grayscale < 255 || !this->ShaderProgramObj) &&
                        (this->viewport->tone.getRed() != 0 || this->viewport->tone.getGreen() != 0 || this->viewport->tone.getBlue() != 0);
    for(size_t r = 0;r < 4;r++){
        //check if need rendering
        //if: normal Texture rendering
        if((this->tone.grayscale < 255 || !this->ShaderProgramObj) && r != 3 ){
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

        //if not: grayscale Texture rendering
        }else if(r == 3 && !(this->ShaderProgramObj && this->tone.grayscale > 0))
            continue;

        //set vColor,tone or grayscale Color
        //vcolors[color][vertices][letter] = vcolors[color + (vertices+letter*4) * 4]
        for(size_t i = 0;i < 4;i++){
            GLubyte rgb[3] = {0,0,0};
            switch(r){
                case 0:
                    vcolors[i*4] = this->vColor[i].red;
                    vcolors[1+i*4] = this->vColor[i].green;
                    vcolors[2+i*4] = this->vColor[i].blue;
                break;
                case 1:
                    ColorTone::ColorTonetoRGB(this->tone,rgb);
                    vcolors[i*4] = rgb[0];
                    vcolors[1+i*4] = rgb[1];
                    vcolors[2+i*4] = rgb[2];
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
                    vcolors[i*4] = 255;
                    vcolors[1+i*4] = 255;
                    vcolors[2+i*4] = 255;
            }
            if(r == 3)
                vcolors[3+i*4] = std::min<uint8>(this->vColor[i].alpha,this->tone.grayscale);
            else
                vcolors[3+i*4] = this->vColor[i].alpha;
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

        if(Sprite::VertexArray){
            glColorPointer(4,GL_UNSIGNED_BYTE, 0, vcolors);
            glDrawArrays(GL_QUADS, 0, 4);
        }else{
            uint i = 0;
            uint j = 0;
            uint k = 0;
            glBegin(GL_QUADS);
            for(;i < 8 || j < 12 || k < 16;i+=2,j+=3,k+=4){
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

    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);

    return 1;
}

void Sprite::copyProperties(const Sprite& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;

        this->SpriteBase::copyProperties(copy);
    }
}

void Sprite::setViewport(Viewport* viewport){
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

