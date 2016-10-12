#include "FontSprite.hpp"

namespace F2C{

GLhandleARB FontSprite::ShaderProgramObj = 0;
TexParam::Tex_Param FontSprite::filter = TexParam::Linear;
bool FontSprite::VertexArray = false;
bool FontSprite::checkVertexArray = false;
uint8 FontSprite::AlphaTolerance = 1;

uint FontSprite::defaultCharsperW = 16;
uint FontSprite::defaultCharsperH = 16;

FontSprite::FontSprite(const FontSprite& copy) :
    SpriteBase(copy),
    clip_rect(NULL),
	viewport(NULL),
    charsperwidth(FontSprite::defaultCharsperW),
    charsperheight(FontSprite::defaultCharsperH),
    biggestCharWidth(0),
    biggestCharHeight(0),
    italic(false)
{
    if(!FontSprite::checkVertexArray){
        FontSprite::VertexArray = uglExtensionSupported("GL_EXT_vertex_array");
        FontSprite::checkVertexArray = true;
    }

	memset(this->char_rect,0,sizeof(this->char_rect[0])*256);

    *this = copy;
}

FontSprite& FontSprite::operator= (const FontSprite& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;
        this->charsperwidth = copy.charsperwidth;
        this->charsperheight = copy.charsperheight;
        this->biggestCharWidth = copy.biggestCharWidth;
        this->biggestCharHeight = copy.biggestCharHeight;
        this->strings = copy.strings;
        this->rect_strings = copy.rect_strings;
        this->italic = copy.italic;
        memcpy(this->char_rect,copy.char_rect,sizeof(this->char_rect[0])*256);

        this->SpriteBase::operator = (copy);

        if (this->pixels){
            this->BuildFont(this->pixels,
                                this->pixelsWidth,
                                this->bitmapWidth,this->bitmapHeight,this->bitmapBits >> 3,
                                this->charsperwidth,this->charsperheight);
        }
    }
    return *this;
}

FontSprite::FontSprite():
    clip_rect(NULL),
	viewport(NULL),
    charsperwidth(FontSprite::defaultCharsperW),
    charsperheight(FontSprite::defaultCharsperH),
    biggestCharWidth(0),
    biggestCharHeight(0),
    italic(false)
{
    if(!FontSprite::checkVertexArray){
        FontSprite::VertexArray = uglExtensionSupported("GL_EXT_vertex_array");
        FontSprite::checkVertexArray = true;
    }

	memset(this->char_rect,0,sizeof(this->char_rect[0])*256);
}

FontSprite::FontSprite(Viewport* viewport):
    clip_rect(NULL),
	viewport(viewport),
	charsperwidth(FontSprite::defaultCharsperW),
    charsperheight(FontSprite::defaultCharsperH),
    biggestCharWidth(0),
    biggestCharHeight(0),
	italic(false)
{
    if(!FontSprite::checkVertexArray){
        FontSprite::VertexArray = uglExtensionSupported("GL_EXT_vertex_array");
        FontSprite::checkVertexArray = true;
    }

	memset(this->char_rect,0,sizeof(this->char_rect[0])*256);

   if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
       this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 )
         this->clip_rect = &this->viewport->clip_rect;
}

FontSprite::FontSprite(const Bitmap* bitmap,uint charsperwidth,uint charsperheight) :
    SpriteBase(bitmap),
    clip_rect(NULL),
	viewport(NULL),
	charsperwidth(charsperwidth),
    charsperheight(charsperheight),
    biggestCharWidth(0),
    biggestCharHeight(0),
    italic(false)
{
    if(!FontSprite::checkVertexArray){
        FontSprite::VertexArray = uglExtensionSupported("GL_EXT_vertex_array");
        FontSprite::checkVertexArray = true;
    }

	memset(this->char_rect,0,sizeof(this->char_rect[0])*256);

    if (bitmap->getPixels()){
        this->BuildFont(bitmap->getPixels(),
                            this->pixelsWidth,
                            this->bitmapWidth,this->bitmapHeight,this->bitmapBits >> 3,
                            this->charsperwidth,this->charsperheight);
    }
}


void FontSprite::setBitmap(const Bitmap* bitmap,uint charsperwidth,uint charsperheight){
	this->charsperwidth = charsperwidth;
	this->charsperheight = charsperheight;

	this->SpriteBase::setBitmap(bitmap);

    if (bitmap){
        if (bitmap->getPixels()){
            this->BuildFont(bitmap->getPixels(),
                                this->pixelsWidth,
                                this->bitmapWidth,this->bitmapHeight,this->bitmapBits >> 3,
                                this->charsperwidth,this->charsperheight);
        }
    }
}

void FontSprite::BuildFont(const ubyte* bitmap,uint pixelswidth,uint width,uint height,uint bytepp,uint charpw,uint charph){
	if(width <= 0 || height <= 0 || !bitmap || charpw <= 0 || charph <= 0)
		return;
	uint cx = 0;
	uint cy = 0;
	uint pcw = width/charpw;
	uint pch = height/charph;
	this->biggestCharWidth = 0;
    this->biggestCharHeight = 0;
	memset(this->char_rect,0,sizeof(this->char_rect[0])*256);

	for (size_t i = 0; i < 256; i++){
	    if (cy >= height)
			break;
        uint sx = cx;
	    uint sy = cy;
	    uint sw = cx+pcw;
	    uint sh = cy+pch;
        if(i == static_cast<size_t>(' ')){ //space
            this->char_rect[i].set(sx,cy,sw-pcw/4,pch);
            cx += pcw;
            if (cx >= width){
                cx = 0;
                cy += pch;
            }
            continue;
        }

        //|->|A | Determines the distance from start to the letter
        uint countx = 0;
        while(sx <= sw){
            if(i == 0 || bytepp < 4)
                break;
            size_t alphai = bytepp*(sx + sy * pixelswidth)+3;
            if(alphai >= width*height*bytepp)
                break;
            if(bitmap[alphai] >= FontSprite::AlphaTolerance)
                break;
            sy++;
            if(sy >= sh){
                sy = cy;
                sx++;
                countx++;
            }
        }
        uint sx2 = cx+pcw;
	    uint sy2 = cy+pch;
	    uint sw2 = cx;
	    uint sh2 = cy;
	    uint countw = 0;
	    //| A|<-| Determines the distance from end to the letter
        while(sx2 >= sw2){
            if(i == 0 || bytepp < 4)
                break;
            size_t alphai = bytepp*(sx2 + sy2 * pixelswidth)+3;
            if(alphai >= width*height*bytepp)
                break;
            if(bitmap[alphai] >= FontSprite::AlphaTolerance)
                break;
            sy2--;
            if(sy2 <= sh2){
                sy2 = cy+pch;
                sx2--;
                countw++;
            }
        }
        /*
        * (cx,cy)                                (pcw,cy)
        *    |---------------------------------------|
             |                                       |
        *    |    |----------char_rect----------|    |
        *    |    |                             |    |
        *    |          (sx,sy)     (sw,sy)          |
        *    |    |--------|-----------|--------|    |
        *    |    |        |           |        |    |
        *    |    |char    |   CHAR    |char    |    |
        *    |    |distance|           |distance|    |
        *    |    |        |           |        |    |
        *    |    |--------|-----------|--------|    |
        *    |          (sx,sh)     (sw,sh)          |
        *    |                                       |
        *    |                                       |
        *    |---------------------------------------|
        * (cx,pch)                               (pcw,pch)
        */

        uint chardistance = (static_cast<int>(pcw/charpw))/2;
        uint crw = static_cast<uint>(std::max<int>(0,(pcw-countx-countw) + chardistance) + 2);
		this->char_rect[i].set(sx - static_cast<int>(chardistance) - 1,cy,crw,pch);
        this->biggestCharWidth = std::max<uint>(this->biggestCharWidth,crw);
        this->biggestCharHeight = std::max<uint>(this->biggestCharHeight,this->char_rect[i].height);

		cx += pcw;
		if (cx >= width){
			cx = 0;
			cy += pch;
		}
	}
	if(this->biggestCharWidth > 0)
        this->char_rect[static_cast<size_t>(' ')].width = static_cast<uint>(static_cast<float>(this->biggestCharWidth)/3.0f);
}

int FontSprite::render() const{
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

    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);

    //for: Texts
    for(size_t i = 0;i < this->strings.size();i++){
        //column coord.
        GLdouble ccx = 0.0f;

        //line coord.
        GLdouble ccy = 0.0f;

        //if: Text outside of clipping Rect or Display
        if(this->clip_rect){
            GLint left1, left2;
            GLint right1, right2;
            GLint top1, top2;
            GLint bottom1, bottom2;

            left1 = this->x+this->rect_strings[i].x;
            left2 = this->clip_rect->x;
            right1 = this->x+this->rect_strings[i].x + this->rect_strings[i].width;
            right2 = this->clip_rect->x + this->clip_rect->width;
            top1 = this->y+this->rect_strings[i].y;
            top2 = this->clip_rect->y;
            bottom1 = this->y+this->rect_strings[i].y + this->rect_strings[i].height;
            bottom2 = this->clip_rect->y + this->clip_rect->height;

            if((bottom1 < top2) || (top1 > bottom2) || (right1 < left2) ||
                (left1 > right2))
                    continue;
        }else{
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            GLint left1, left2;
            GLint right1, right2;
            GLint top1, top2;
            GLint bottom1, bottom2;

            left1 = this->x+this->rect_strings[i].x;
            left2 = viewport[0];
            right1 = this->x+this->rect_strings[i].x + this->rect_strings[i].width;
            right2 = viewport[0] + viewport[2];
            top1 = this->y+this->rect_strings[i].y;
            top2 = viewport[1];
            bottom1 = this->y+this->rect_strings[i].y + this->rect_strings[i].height;
            bottom2 = viewport[1] + viewport[3];

            if((bottom1 < top2) || (top1 > bottom2) || (right1 < left2) ||
                (left1 > right2))
                    continue;
        }

        glLoadIdentity();
        glTranslated(this->x+this->rect_strings[i].x,
                this->y+this->rect_strings[i].y,
                (this->z + ((this->viewport)? this->viewport->z : 0))*100.0f);
        glRotated(this->angle_x,1.0f,0.0f,0.0f);
        glRotated(this->angle_y,0.0f,1.0f,0.0f);
        glRotated(this->angle_z,0.0f,0.0f,1.0f);
        glScaled(this->zoom_x,this->zoom_y,1.0f);

        //set src_rect of Texts
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        GLint clippedLeft = this->x+this->rect_strings[i].x;
        GLint clippedTop = this->y+this->rect_strings[i].y;
        GLint clippedRight = this->x+this->rect_strings[i].x+this->rect_strings[i].width;
        GLint clippedBottom = this->y+this->rect_strings[i].y+this->rect_strings[i].height;

        if(this->src_rect.width > 0 && this->src_rect.height > 0){
            clippedLeft = std::max(this->x+this->src_rect.x,clippedLeft);
            clippedTop = std::max(this->y+this->src_rect.y,clippedTop);
            clippedRight = std::min<int>(this->x+this->src_rect.x+this->src_rect.width,clippedRight);
            clippedBottom = std::min<int>(this->y+this->src_rect.y+this->src_rect.height,clippedBottom);
        }
        if(this->clip_rect){
            clippedLeft = std::max(this->clip_rect->x,clippedLeft);
            clippedTop = std::max(this->clip_rect->y,clippedTop);
            clippedRight = std::min<int>(this->clip_rect->x+this->clip_rect->width,clippedRight);
            clippedBottom = std::min<int>(this->clip_rect->y+this->clip_rect->height,clippedBottom);
        }

        glScissor(clippedLeft, viewport[3] - clippedBottom, clippedRight - clippedLeft, clippedBottom);

        //2D-Array of texcoord,vertices and colors
        //texcoord[letter] = {x,y,            width,y,
        //                    width,height,   x,height}
        //vertices[letter] = {x,y,z,            width,y,z,
        //                    width,height,z,   x,height,z}
        //vcolors[letter] =  {r,g,b,a,        r,g,b,a,
        //                    r,g,b,a,        r,g,b,a}
        GLdouble* texcoord = new GLdouble[this->strings[i].length()*8]();
        GLdouble* vertices = new GLdouble[this->strings[i].length()*12]();
        GLubyte* vcolors = new GLubyte[this->strings[i].length()*16]();

        GLdouble invW = 1.0f / texW;
        GLdouble invH = 1.0f / texH;
        size_t strlength = this->strings[i].length();
        std::string str = this->strings[i];

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        //for: set texcoord and vertices of all letter of string
        for(size_t j = 0;j < strlength;j++){
            size_t cid = static_cast<size_t>(str[j]);
            uint charw = this->char_rect[cid].width;
            uint charh = this->char_rect[cid].height;

            //texcoord: top
            GLdouble cx = this->char_rect[cid].x * invW;
            if( cx > 1.0f){ cx = 1.0f;}
            else if( cx < 0.0f ){cx = 0.0f;}

            //texcoord: left
            GLdouble cy = this->char_rect[cid].y * invH;
            if( cy > 1.0f){ cy = 1.0f;}
            else if( cy < 0.0f ){cy = 0.0f;}

            //texcoord: right
            GLdouble cwidth = (this->char_rect[cid].x+charw) * invW;
            if( cwidth > 1.0f){ cwidth = 1.0f;}
            else if( cwidth < 0.0f ){cwidth = 0.0f;}

            //texcoord: bottom
            GLdouble cheight = (this->char_rect[cid].y+charh) * invH;
            if( cheight > 1.0f){ cheight = 1.0f;}
            else if( cheight < 0.0f ){cheight = 0.0f;}

            cx = std::min(cx,cwidth);
            cy = std::min(cy,cheight);

            //set texcoord of one letter
            texcoord[0+j*8] = cx;
            texcoord[1+j*8] = cy;
            texcoord[2+j*8] = cwidth;
            texcoord[3+j*8] = cy;
            texcoord[4+j*8] = cwidth;
            texcoord[5+j*8] = cheight;
            texcoord[6+j*8] = cx;
            texcoord[7+j*8] = cheight;

            //set vertices of one letter
            vertices[0+j*12] = ccx + ((this->italic)? charw*0.125f : 0.0f);
            vertices[1+j*12] = ccy;
            vertices[2+j*12] = 0.0f;

            vertices[3+j*12] = ccx + charw + ((this->italic)? charw*0.125f : 0.0f);
            vertices[4+j*12] = ccy;
            vertices[5+j*12] = 0.0f;

            vertices[6+j*12] = ccx + charw;
            vertices[7+j*12] = ccy + charh;
            vertices[8+j*12] = 0.0f;

            vertices[9+j*12] = ccx;
            vertices[10+j*12] = ccy + charh;
            vertices[11+j*12] = 0.0f;

            if(str[j] == '\n'){
                ccy += this->biggestCharHeight+1;
                ccx = 0.0f;
                continue;
            }else if(str[j] == '\t'){
                ccx += this->char_rect[static_cast<size_t>(' ')].width*3.0f;
                continue;
            }else if(str[j] == '\v'){
                ccy += this->char_rect[static_cast<size_t>(' ')].height*3.0f;
                continue;
            }

            ccx += charw;
        }

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
            for(size_t l = 0;l < strlength;l++){
                for(size_t i = 0;i < 4;i++){
                    GLubyte rgb[3] = {0,0,0};
                    switch(r){
                        case 0:
                            vcolors[(i+l*4)*4] = this->vColor[i].red;
                            vcolors[1+(i+l*4)*4] = this->vColor[i].green;
                            vcolors[2+(i+l*4)*4] = this->vColor[i].blue;
                        break;
                        case 1:
                            ColorTone::ColorTonetoRGB(this->tone,rgb);
                            vcolors[(i+l*4)*4] = rgb[0];
                            vcolors[1+(i+l*4)*4] = rgb[1];
                            vcolors[2+(i+l*4)*4] = rgb[2];
                        break;
                        case 2:
                            if(this->viewport){
                                ColorTone::ColorTonetoRGB(this->viewport->tone,rgb);
                                vcolors[(i+l*4)*4] = rgb[0];
								vcolors[1+(i+l*4)*4] = rgb[1];
								vcolors[2+(i+l*4)*4] = rgb[2];
                            }
                        default:
                            vcolors[(i+l*4)*4] = 255;
                            vcolors[1+(i+l*4)*4] = 255;
                            vcolors[2+(i+l*4)*4] = 255;
                    }
                    if(r == 3)
                        vcolors[3+(i+l*4)*4] = std::min<uint8>(this->vColor[i].alpha,this->tone.grayscale);
                    else
                        vcolors[3+(i+l*4)*4] = this->vColor[i].alpha;
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

            if(FontSprite::VertexArray){
                glColorPointer(4,GL_UNSIGNED_BYTE, 0, vcolors);
                glDrawArrays(GL_QUADS, 0, strlength*4);
            }else{
                uint i = 0;
                uint j = 0;
                uint k = 0;
                glBegin(GL_QUADS);
                for(;i < strlength*8 || j < strlength*12 || k < strlength*16;i+=2,j+=3,k+=4){
                    glColor4ubv(&vcolors[k]);
                    glTexCoord2dv(&texcoord[i]);
                    glVertex3dv(&vertices[j]);
                }
                glEnd();
            }

            if(r == 3)
                glUseProgramObjectARB(0);
        }

        delete[] vcolors;
        delete[] texcoord;
        delete[] vertices;
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

void FontSprite::copyProperties(const FontSprite& copy){
    if(this != &copy){
        this->clip_rect = copy.clip_rect;
        this->viewport = copy.viewport;
        this->tone = copy.tone;
        this->strings = copy.strings;
        this->rect_strings = copy.rect_strings;
        this->italic = copy.italic;

        this->SpriteBase::copyProperties(copy);
    }
}

void FontSprite::addText(int x,int y,uint width,uint height,std::string text){
	this->strings.push_back(text);
	this->rect_strings.push_back(Rect (x,y,width,height));
}

void FontSprite::addText(const Rect& rect,std::string text){
	this->strings.push_back(text);
	this->rect_strings.push_back(rect);
}

void FontSprite::clearTexts(){
	this->strings.clear();
	this->rect_strings.clear();
}

void FontSprite::setViewport(Viewport* viewport){
    this->viewport = viewport;
    if(!this->viewport){
        this->clip_rect = NULL;
    }else if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
                this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 ){
                    this->clip_rect = &this->viewport->clip_rect;
    }
}

uint FontSprite::getCharsperWidth() const {return this->charsperwidth;}
uint FontSprite::getCharsperHeight() const {return this->charsperheight;}
const std::vector<std::string>& FontSprite::getTexts() const {return this->strings;}
const std::vector<Rect>& FontSprite::getTextsRect() const {return this->rect_strings;}
const Rect* FontSprite::getCharsRect() const {return this->char_rect;}

};

