#include <Fantasy2C/SimpleSprite.hpp>

namespace F2C{

GLhandleARB SimpleSprite::ShaderProgramObj = 0;
TexParam::Tex_Param SimpleSprite::filter = TexParam::Linear;
bool SimpleSprite::VertexArray = false;
bool SimpleSprite::checkVertexArray = false;

SimpleSprite::SimpleSprite(const SimpleSprite& copy){
    if(!SimpleSprite::checkVertexArray){
        SimpleSprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        SimpleSprite::checkVertexArray = true;
    }

    this->SpriteBase::operator = (copy);
}

SimpleSprite& SimpleSprite::operator= (const SimpleSprite& copy){
    if(this != &copy){
        this->SpriteBase::operator = (copy);
    }
    return *this;
}


SimpleSprite::SimpleSprite():
    grayscale(0)
{
    if(!SimpleSprite::checkVertexArray){
        SimpleSprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        SimpleSprite::checkVertexArray = true;
    }
}

SimpleSprite::SimpleSprite(const Bitmap* bitmap):
    SpriteBase(bitmap),
    grayscale(0)
{
    if(!SimpleSprite::checkVertexArray){
        SimpleSprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        SimpleSprite::checkVertexArray = true;
    }
}

int SimpleSprite::render() const{
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

    if(this->bitmapWidth > 0 || this->bitmapHeight > 0)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);

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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(this->blend_type == BlendType::additives)
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    else if(this->blend_type == BlendType::normal)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    else if(this->blend_type == BlendType::multiplicative)
        glBlendFunc(GL_DST_COLOR,GL_ZERO);

    glLoadIdentity();
    glTranslated(this->x+(static_cast<double>(srect.width)/2.0f),
                  this->y+(static_cast<double>(srect.height)/2.0f),
                  this->z*100.0f);
    glRotated(this->angle_x,1.0f,0.0f,0.0f);
    glRotated(this->angle_y,0.0f,1.0f,0.0f);
    glRotated(this->angle_z,0.0f,0.0f,1.0f);
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
    GLdouble texcoord[8] = {srect.x/texW,
                            srect.y/texH,

                            (srect.x+srect.width)/texW,
                            srect.y/texH,


                            (srect.x+srect.width)/texW,
                            (srect.y+srect.height)/texH,

                            srect.x/texW,
                            (srect.y+srect.height)/texH};

    GLdouble vertices[12] = {0.0f,0.0f,0.0f,
                           srect.width,0.0f,0.0f,
                           srect.width,srect.height,0.0f,
                           0.0f,srect.height,0.0f,};

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

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);

    glTexCoordPointer(2, GL_DOUBLE, 0, texcoord);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);

    if(!this->ShaderProgramObj || this->grayscale < 255){
        GLubyte vcolors[16] = {this->vColor[0].red,this->vColor[0].green,this->vColor[0].blue,this->vColor[0].alpha,
                                this->vColor[1].red,this->vColor[1].green,this->vColor[1].blue,this->vColor[1].alpha,
                                this->vColor[2].red,this->vColor[2].green,this->vColor[2].blue,this->vColor[2].alpha,
                                this->vColor[3].red,this->vColor[3].green,this->vColor[3].blue,this->vColor[3].alpha};

        if(SimpleSprite::VertexArray){
            glColorPointer(4,GL_UNSIGNED_BYTE, 0, vcolors);
            glDrawArrays(GL_QUADS, 0, 4);
        }else{
            size_t i = 0;
            size_t j = 0;
            size_t k = 0;
            glBegin(GL_QUADS);
            for(;i < 8 || j < 12 || k < 16;i+=2,j+=3,k+=4){
                glColor4ubv(&vcolors[k]);
                glTexCoord2dv(&texcoord[i]);
                glVertex3dv(&vertices[j]);
            }
            glEnd();
        }
    }
    if(this->ShaderProgramObj && this->grayscale > 0){
        GLubyte vcolors[16] = {255,255,255,std::min<GLubyte>(this->vColor[0].alpha,this->grayscale),
                                255,255,255,std::min<GLubyte>(this->vColor[1].alpha,this->grayscale),
                                255,255,255,std::min<GLubyte>(this->vColor[2].alpha,this->grayscale),
                                255,255,255,std::min<GLubyte>(this->vColor[3].alpha,this->grayscale)};
        glUseProgramObjectARB( this->ShaderProgramObj );
        if(SimpleSprite::VertexArray){
            glColorPointer(4,GL_UNSIGNED_BYTE, 0, &vcolors);
            glDrawArrays(GL_QUADS, 0, 4);
        }else{
            size_t i = 0;
            size_t j = 0;
            size_t k = 0;
            glBegin(GL_QUADS);
            for(;i < 8 || j < 12 || k < 16;i+=2,j+=3,k+=4){
                glColor4ubv(&vcolors[k]);
                glTexCoord2dv(&texcoord[i]);
                glVertex3dv(&vertices[j]);
            }
            glEnd();
        }
        glUseProgramObjectARB( 0 );
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);

	return 1;
}

void SimpleSprite::copyProperties(const SimpleSprite& copy){
    if(this != &copy)
        this->SpriteBase::copyProperties(copy);
}

};

