#include <Fantasy2C/ArraySprite.hpp>

namespace F2C{

GLhandleARB ArraySprite::ShaderProgramObj = 0;
TexParam::Tex_Param ArraySprite::filter = TexParam::Linear;
bool ArraySprite::VertexArray = false;
bool ArraySprite::checkVertexArray = false;

SpriteElement::SpriteElement():
	src_rect(0,0,0,0),
	show(true),
	x(0),y(0),z(0),
	zoom_x(1.0),zoom_y(1.0),
	angle_x(0),
	angle_y(0),
	angle_z(0),
	flippedH(false),
    flippedV(false)
{
	for (uint8 i = 0; i < 4;i++)
		vColor[i].set(255,255,255,255);
}

void SpriteElement::setRed(uint8 red){
    for (uint8 i = 0; i < 4;i++)
        this->vColor[i].red = red;
}
void SpriteElement::setGreen(uint8 green){
    for (uint8 i = 0; i < 4;i++)
        this->vColor[i].green = green;
}
void SpriteElement::setBlue(uint8 blue){
    for (uint8 i = 0; i < 4;i++)
        this->vColor[i].blue = blue;
}
void SpriteElement::setAlpha(uint8 alpha){
    for (uint8 i = 0; i < 4;i++)
        this->vColor[i].alpha = alpha;
}

void SpriteElement::setColor(const Color& color){
    for (uint8 i = 0; i < 4;i++)
        this->vColor[i] = color;
}
void SpriteElement::setColor(uint8 red,uint8 green,uint8 blue,uint8 alpha){
    for (uint8 i = 0; i < 4;i++)
        this->vColor[i].set(red,green,blue,alpha);
}
void SpriteElement::setColor(uint8 red,uint8 green,uint8 blue){
    for (uint8 i = 0; i < 4;i++)
        this->vColor[i].set(red,green,blue);
}

ArraySprite::~ArraySprite(){
    if(this->texture)
        glDeleteTextures(1,&this->texture);
    if(this->pixels)
        delete[] this->pixels;
}

ArraySprite::ArraySprite(const ArraySprite& copy):
    texture(0),
	bitmapWidth(0),
    bitmapHeight(0),
    pixelsWidth(0),
    pixels(NULL),
    bitmapFormat(Image::RGBA),
    bitmapBits(0),
	viewport(NULL),
	clip_rect(NULL),
	x(0),y(0),z(0),
	zoom_x(1.0),zoom_y(1.0),
	blend_type(BlendType::normal)
{
    if(!ArraySprite::checkVertexArray){
        ArraySprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        ArraySprite::checkVertexArray = true;
    }

    *this = copy;
}

ArraySprite& ArraySprite::operator= (const ArraySprite& copy){
    if(this != &copy){
        this->viewport = copy.viewport;
        this->clip_rect = copy.clip_rect;
        this->bitmapWidth = copy.bitmapWidth;
        this->bitmapHeight = copy.bitmapHeight;
        this->bitmapFormat = copy.bitmapFormat;
        this->pixelsWidth = copy.pixelsWidth;
        this->bitmapBits = copy.bitmapBits;
		this->x = copy.x;
		this->y = copy.y;
		this->z = copy.z;
		this->zoom_x = copy.zoom_y;
		this->zoom_y = copy.zoom_y;
		this->blend_type = copy.blend_type;
		this->tone = copy.tone;

		this->elements = copy.elements;

        if(!this->texture)
          glGenTextures(1, &this->texture);

        if(this->pixels)
            delete[] pixels;
        this->pixels = NULL;

        if(copy.pixels){
            this->pixels = new ubyte[this->pixelsWidth*this->pixelsWidth*(this->bitmapBits >> 3)];
            memcpy(this->pixels,copy.pixels,(this->pixelsWidth*this->pixelsWidth*(this->bitmapBits >> 3))*sizeof(ubyte));
        }

        if (this->bitmapWidth > 0 && this->bitmapHeight > 0){
            glBindTexture(GL_TEXTURE_2D, this->texture);
			glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(bitmapFormat),
                            this->pixelsWidth,
                            this->pixelsWidth,
                            0, static_cast<GLenum>(bitmapFormat),
                            GL_UNSIGNED_BYTE, this->pixels);
        }
    }
    return *this;
}

ArraySprite::ArraySprite():
   texture(0),
	bitmapWidth(0),
    bitmapHeight(0),
    pixelsWidth(0),
    pixels(NULL),
    bitmapFormat(Image::RGBA),
    bitmapBits(0),
	viewport(NULL),
	clip_rect(NULL),
	x(0),y(0),z(0),
	zoom_x(1.0),zoom_y(1.0),
	blend_type(BlendType::normal)
{
    if(!ArraySprite::checkVertexArray){
        ArraySprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        ArraySprite::checkVertexArray = true;
    }

	glGenTextures(1, &this->texture);
}

ArraySprite::ArraySprite(const Bitmap* bitmap):
    texture(0),
	bitmapWidth(0),
    bitmapHeight(0),
    pixelsWidth(0),
    pixels(NULL),
    bitmapFormat(Image::RGBA),
    bitmapBits(0),
	viewport(NULL),
	clip_rect(NULL),
	x(0),y(0),z(0),
	zoom_x(1.0),zoom_y(1.0),
	blend_type(BlendType::normal)
{
    if(!ArraySprite::checkVertexArray){
        ArraySprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        ArraySprite::checkVertexArray = true;
    }

    glGenTextures(1, &this->texture);

    if (bitmap){
        if (bitmap->getPixels()){
            this->bitmapWidth = bitmap->getWidth();
            this->bitmapHeight = bitmap->getHeight();
            this->pixelsWidth = bitmap->getPixelsWidth();
            this->bitmapBits = bitmap->getBits();
            this->bitmapFormat = bitmap->getDataFormat();
            if(this->pixels)
                delete[] this->pixels;
            this->pixels = new ubyte[bitmap->getPixelsSize()];
            memcpy(this->pixels,bitmap->getPixels(),bitmap->getPixelsSize()*sizeof(ubyte));
            glBindTexture(GL_TEXTURE_2D, this->texture);
            glTexImage2D(GL_TEXTURE_2D, 0, 4,
                            this->pixelsWidth,
                            this->pixelsWidth,
                            0, static_cast<GLenum>(this->bitmapFormat),
                            GL_UNSIGNED_BYTE, this->pixels);
        }
    }
}

ArraySprite::ArraySprite(Viewport* viewport):
    texture(0),
	bitmapWidth(0),
    bitmapHeight(0),
    pixelsWidth(0),
    pixels(NULL),
    bitmapFormat(Image::RGBA),
    bitmapBits(0),
	viewport(viewport),
	clip_rect(NULL),
	x(0),y(0),z(0),
	zoom_x(1.0),zoom_y(1.0),
	blend_type(BlendType::normal)
{
    if(!ArraySprite::checkVertexArray){
        ArraySprite::VertexArray = glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE;
        ArraySprite::checkVertexArray = true;
    }

   if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
       this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 )
         this->clip_rect = &this->viewport->clip_rect;

    glGenTextures(1, &this->texture);
}

int ArraySprite::render() const{
    if(this->elements.empty())
		return -4;
	return this->render(0,this->elements.size());
}

int ArraySprite::render(size_t starteid) const{
    if(this->elements.empty())
		return -4;
	return this->render(starteid,this->elements.size());
}

int ArraySprite::render(size_t starteid,size_t endeid) const{
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
		if(!element->show)
			continue;

		//if: Alpha Color == 0
		if(element->vColor[0].alpha < 1 &&
			element->vColor[1].alpha < 1 &&
			element->vColor[2].alpha < 1 &&
			element->vColor[3].alpha < 1){
				continue;
		}

		//if: Zoom-Factor == 0
		if(element->zoom_x == 0.0f || element->zoom_y == 0.0f)
			continue;

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
        if(texW == 0 || texH == 0)
            continue;

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

			left1 = this->x+element->x;
			left2 = this->clip_rect->x;
			right1 = this->x+element->x + srect.width;
			right2 = this->clip_rect->x + this->clip_rect->width;
			top1 = this->y+element->y;
			top2 = this->clip_rect->y;
			bottom1 = this->y+element->y + srect.height;
			bottom2 = this->clip_rect->y + this->clip_rect->height;

			if((bottom1 < top2) || (top1 > bottom2) || (right1 < left2) ||
				(left1 > right2))
					continue;
		}else{
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			int left1, left2;
			int right1, right2;
			int top1, top2;
			int bottom1, bottom2;

			left1 = this->x+element->x;
			left2 = viewport[0];
			right1 = this->x+element->x + srect.width;
			right2 = viewport[0] + viewport[2];
			top1 = this->y+element->y;
			top2 = viewport[1];
			bottom1 = this->y+element->y + srect.height;
			bottom2 = viewport[1] + viewport[3];

			if((bottom1 < top2) || (top1 > bottom2) || (right1 < left2) ||
				(left1 > right2))
					continue;
		}

		GLdouble invW = 1.0f / texW;
		GLdouble invH = 1.0f / texH;

		//set texcoord of Texture
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
        GLdouble vwidth = srect.width * element->zoom_x;

        //vertex: bottom
        GLdouble vheight = srect.height * element->zoom_y;

		texcoord[e*8] = cx;
		texcoord[1+e*8] = cy;

		texcoord[2+e*8] = cwidth;
		texcoord[3+e*8] = cy;

		texcoord[4+e*8] = cwidth;
		texcoord[5+e*8] = cheight;

		texcoord[6+e*8] = cx;
		texcoord[7+e*8] = cheight;

		vertices[e*12] = element->x;
		vertices[1+e*12] = element->y;
		vertices[2+e*12] = element->z*100.0f;

		vertices[3+e*12] = element->x+vwidth;
		vertices[4+e*12] = element->y;
		vertices[5+e*12] = element->z*100.0f;

		vertices[6+e*12] = element->x+vwidth;
		vertices[7+e*12] = element->y+vheight;
		vertices[8+e*12] = element->z*100.0f;

		vertices[9+e*12] = element->x;
		vertices[10+e*12] = element->y+vheight;
		vertices[11+e*12] = element->z*100.0f;

        if(element->angle_z != 0.0f){
			GLdouble angle = element->angle_z * (3.14159265358979323f / 180.0f); //convert Grad in Rad(1 Rad = PI/180)
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

		//vcolors[element] =  {r,g,b,a,        r,g,b,a,
		//					   r,g,b,a,        r,g,b,a}
		for(size_t i = 0;i < 4;i++){
			vcolors[(i+e*4)*4] = element->vColor[i].red;
			vcolors[1+(i+e*4)*4] = element->vColor[i].green;
			vcolors[2+(i+e*4)*4] = element->vColor[i].blue;
			vcolors[3+(i+e*4)*4] = element->vColor[i].alpha;
		}

		if(element->flippedH){
		    std::swap(texcoord[e*8],texcoord[2+e*8]);
		    std::swap(texcoord[4+e*8],texcoord[6+e*8]);
        }
        if(element->flippedV){
		    std::swap(texcoord[1+e*8],texcoord[7+e*8]);
		    std::swap(texcoord[3+e*8],texcoord[5+e*8]);
        }
	}

	//set clipping Rect
    if(this->clip_rect){
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        int clippedLeft = this->clip_rect->x;
        int clippedTop = this->clip_rect->y;
        int clippedRight = clippedLeft + this->clip_rect->width;
        int clippedBottom = clippedTop + this->clip_rect->height;

        // translate from top left to bottom left coordinate system
        glScissor(clippedLeft, viewport[3] - clippedBottom, clippedRight - clippedLeft, clippedBottom);
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

	glLoadIdentity();
	glTranslated(this->x, this->y,
				  (this->z + ((this->viewport)? this->viewport->z : 0))*100.0f);
	glScaled(this->zoom_x,this->zoom_y,1.0f);

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
        //vcolors[element][color][vertices] = vcolors[color + (vertices+elemet*4) * 4]
        for(size_t e = 0;e < esize;e++){
			if(r == 0)
				break;
            for(size_t i = 0;i < 4;i++){
                GLubyte rgb[3] = {0,0,0};
                switch(r){
                    case 1:
                        ColorTone::ColorTonetoRGB(this->tone,rgb);
                        vcolors[(i+e*4)*4] = rgb[0];
                        vcolors[1+(i+e*4)*4] = rgb[1];
                        vcolors[2+(i+e*4)*4] = rgb[2];
                    break;
                    case 2:
                        if(this->viewport){
                            ColorTone::ColorTonetoRGB(this->viewport->tone,rgb);
                            vcolors[(i+e*4)*4] = rgb[0];
							vcolors[1+(i+e*4)*4] = rgb[1];
							vcolors[2+(i+e*4)*4] = rgb[2];
                        }
                    default:
                        vcolors[(i+e*4)*4] = 255;
                        vcolors[1+(i+e*4)*4] = 255;
                        vcolors[2+(i+e*4)*4] = 255;
                }
                if(r == 3)
                    vcolors[3+(i+e*4)*4] = std::min<uint8>(this->elements[e].vColor[i].alpha,this->tone.grayscale);
                else
                    vcolors[3+(i+e*4)*4] = this->elements[e].vColor[i].alpha;
            }
        }

        glShadeModel(GL_SMOOTH);

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

        if(ArraySprite::VertexArray){
            glColorPointer(4,GL_UNSIGNED_BYTE, 0, vcolors);
            glDrawArrays(GL_QUADS, 0, esize*4);
        }else{
            uint i = 0;
            uint j = 0;
            uint k = 0;
            glBegin(GL_QUADS);
            for(;i < esize*12 || j < esize*8 || k < esize*16;i+=3,j+=2,k+=4){
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

void ArraySprite::setBitmap(const Bitmap* bitmap){
	if(!this->texture)
      glGenTextures(1, &this->texture);

    if (bitmap){
        if (bitmap->getPixels()){
            this->bitmapWidth = bitmap->getWidth();
            this->bitmapHeight = bitmap->getHeight();
            this->pixelsWidth = bitmap->getPixelsWidth();
            this->bitmapBits = bitmap->getBits();
            this->bitmapFormat = bitmap->getDataFormat();
            if(this->pixels)
                delete[] this->pixels;
            this->pixels = new ubyte[bitmap->getPixelsSize()];
            memcpy(this->pixels,bitmap->getPixels(),bitmap->getPixelsSize()*sizeof(ubyte));
            glBindTexture(GL_TEXTURE_2D, this->texture);
            glTexImage2D(GL_TEXTURE_2D, 0, 4,
                            this->pixelsWidth,
                            this->pixelsWidth,
                            0, static_cast<GLenum>(this->bitmapFormat),
                            GL_UNSIGNED_BYTE, this->pixels);
            return;
        }
    }
    if(this->pixels)
        delete[] this->pixels;
    this->pixels = NULL;
    this->bitmapWidth = 0;
    this->bitmapHeight = 0;
    this->pixelsWidth = 0;
    this->bitmapBits = 0;
    this->bitmapFormat = Image::RGBA;
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4,
                        0,
                        0,
                        0, static_cast<GLenum>(this->bitmapFormat),
                        GL_UNSIGNED_BYTE, NULL);
}

void ArraySprite::setViewport(Viewport* viewport){
    this->viewport = viewport;
    if(!this->viewport){
        this->clip_rect = NULL;
    }else if(this->viewport->clip_rect.x != 0 || this->viewport->clip_rect.y != 0 ||
                this->viewport->clip_rect.height != 0  || this->viewport->clip_rect.width != 0 ){
                    this->clip_rect = &this->viewport->clip_rect;
    }
}

uint ArraySprite::getTexWidth() const {return this->bitmapWidth;}
uint ArraySprite::getTexHeight() const {return this->bitmapHeight;}
uint ArraySprite::getTexBits() const {return this->bitmapBits;}
Image::DataFormat ArraySprite::getTexDataFormat() const {return this->bitmapFormat;}

uint ArraySprite::getTexture() const {return this->texture;}

};

