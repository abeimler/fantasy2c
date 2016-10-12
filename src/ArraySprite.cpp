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
	for (uint8 i = 0; i < 4;++i)
		vColor[i].set(255,255,255,255);
}

void SpriteElement::setRed(uint8 red){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].red = red;
}
void SpriteElement::setGreen(uint8 green){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].green = green;
}
void SpriteElement::setBlue(uint8 blue){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].blue = blue;
}
void SpriteElement::setAlpha(uint8 alpha){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].alpha = alpha;
}

void SpriteElement::setColor(const Color& color){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i] = color;
}
void SpriteElement::setColor(uint8 red,uint8 green,uint8 blue,uint8 alpha){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].set(red,green,blue,alpha);
}
void SpriteElement::setColor(uint8 red,uint8 green,uint8 blue){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].set(red,green,blue);
}


void ArraySprite::enableGLDrawArray(bool enable){
    ArraySprite::VertexArray = enable;
    ArraySprite::checkVertexArray = true;
}
bool ArraySprite::isEnableGLDrawArray(){
    return ArraySprite::VertexArray;
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
    if(!ArraySprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        ArraySprite::enableGLDrawArray(true);
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

        if(this->pixels)
            delete[] pixels;
        this->pixels = NULL;

        if(copy.pixels){
            this->pixels = new ubyte[this->pixelsWidth*this->pixelsWidth*(this->bitmapBits >> 3)];
            memcpy(this->pixels,copy.pixels,(this->pixelsWidth*this->pixelsWidth*(this->bitmapBits >> 3))*sizeof(ubyte));
        }

        if (this->bitmapWidth > 0 && this->bitmapHeight > 0){
            if(!this->texture)
                glGenTextures(1, &this->texture);

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
    if(!ArraySprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        ArraySprite::enableGLDrawArray(true);
    }
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
    if(!ArraySprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        ArraySprite::enableGLDrawArray(true);
    }

    this->setBitmap(bitmap);
}

ArraySprite::ArraySprite(Viewport* viewport):
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
    if(!ArraySprite::checkVertexArray && glfwExtensionSupported("GL_ARB_vertex_buffer_object") == GL_TRUE){
        ArraySprite::enableGLDrawArray(true);
    }

   this->setViewport(viewport);
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
    }else{
        this->clip_rect = NULL;
    }
}

uint ArraySprite::getTexWidth() const {return this->bitmapWidth;}
uint ArraySprite::getTexHeight() const {return this->bitmapHeight;}
uint ArraySprite::getTexBits() const {return this->bitmapBits;}
Image::DataFormat ArraySprite::getTexDataFormat() const {return this->bitmapFormat;}

uint ArraySprite::getTexture() const {return this->texture;}

};

