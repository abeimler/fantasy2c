#include <Fantasy2C/SpriteBase.hpp>

namespace F2C{

SpriteBase::~SpriteBase(){
    if(this->texture)
        glDeleteTextures(1,&this->texture);
    if(this->pixels)
        delete[] this->pixels;
}

SpriteBase::SpriteBase(const SpriteBase& copy):
    texture(0),
	bitmapWidth(0),
    bitmapHeight(0),
    pixelsWidth(0),
    pixels(NULL),
    bitmapFormat(Image::RGBA),
    bitmapBits(0),
	src_rect(0,0,0,0),
	show(true),
	x(0),y(0),z(0),
	zoom_x(1.0),zoom_y(1.0),
	angle_x(0),
	angle_y(0),
	angle_z(0),
	blend_type(BlendType::normal),
	flippedH(false),
    flippedV(false)
{
    *this = copy;
}

SpriteBase& SpriteBase::operator= (const SpriteBase& copy){
    if(this != &copy){
        this->src_rect = copy.src_rect;
        this->show = copy.show;
        this->x = copy.x;
        this->y = copy.y;
        this->z = copy.z;
        this->zoom_x = copy.zoom_x;
        this->zoom_y = copy.zoom_y;
        this->angle_x = copy.angle_x;
        this->angle_y = copy.angle_y;
        this->angle_z = copy.angle_z;
        this->blend_type = copy.blend_type;
        this->bitmapWidth = copy.bitmapWidth;
        this->bitmapHeight = copy.bitmapHeight;
        this->bitmapFormat = copy.bitmapFormat;
        this->pixelsWidth = copy.pixelsWidth;
        this->bitmapBits = copy.bitmapBits;
        this->flippedH = copy.flippedH;
        this->flippedV = copy.flippedV;
        for (uint8 i = 0; i < 4;++i)
            this->vColor[i] = copy.vColor[i];

        if(this->pixels)
            delete[] this->pixels;
        this->pixels = NULL;

        if(copy.pixels){
            this->pixels = new ubyte[this->pixelsWidth*this->pixelsWidth*(this->bitmapBits >> 3)];
            memcpy(this->pixels,copy.pixels,(this->pixelsWidth*this->pixelsWidth*(this->bitmapBits >> 3))*sizeof(ubyte));
        }

        if (this->pixels && this->bitmapWidth > 0 && this->bitmapHeight > 0){
            if(!this->texture)
                glGenTextures(1, &this->texture);

            glBindTexture(GL_TEXTURE_2D, this->texture);
            glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(this->bitmapFormat),
                            this->pixelsWidth,
                            this->pixelsWidth,
                            0, static_cast<GLenum>(this->bitmapFormat),
                            GL_UNSIGNED_BYTE, this->pixels);
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out,const SpriteBase& copy){
    int itype = static_cast<int>(copy.blend_type);
    int iformat = static_cast<int>(copy.bitmapFormat);

    out << copy.src_rect;
    out << copy.show;
    out << copy.x;
    out << copy.y;
    out << copy.z;
    out << copy.zoom_x;
    out << copy.zoom_y;
    out << copy.angle_x;
    out << copy.angle_y;
    out << copy.angle_z;
    out << itype;
    out << copy.bitmapWidth;
    out << copy.bitmapHeight;
    out << iformat;
    out << copy.pixelsWidth;
    out << copy.bitmapBits;
    out << copy.flippedH;
    out << copy.flippedV;
    for (uint8 i = 0; i < 4;++i)
        out << copy.vColor[i];

    size_t psize = copy.pixelsWidth*copy.pixelsWidth*(copy.bitmapBits >> 3);
    if(!copy.pixels)
        psize = 0;

    out << psize;
    if(copy.pixels){
        for(size_t i = 0;i < psize;++i)
            out << copy.pixels[i];
    }

    return out;
}

std::istream& operator>>(std::istream &in, SpriteBase& copy){
    int itype = 0;
    int iformat = 0;

    in >> copy.src_rect;
    in >> copy.show;
    in >> copy.x;
    in >> copy.y;
    in >> copy.z;
    in >> copy.zoom_x;
    in >> copy.zoom_y;
    in >> copy.angle_x;
    in >> copy.angle_y;
    in >> copy.angle_z;
    in >> itype;
    in >> copy.bitmapWidth;
    in >> copy.bitmapHeight;
    in >> iformat;
    in >> copy.pixelsWidth;
    in >> copy.bitmapBits;
    in >> copy.flippedH;
    in >> copy.flippedV;

    copy.blend_type = static_cast<BlendType::Blend_Type>(itype);
    copy.bitmapFormat = static_cast<Image::DataFormat>(iformat);

    for (uint8 i = 0; i < 4;++i)
        in >> copy.vColor[i];

    size_t psize = 0;
    in >> psize;
    if(psize > 0){
        if(copy.pixels)
            delete[] copy.pixels;

        copy.pixels = new ubyte[psize];
        for(size_t i = 0;i < psize;++i)
            in >> copy.pixels[i];

        if (copy.pixels && copy.bitmapWidth > 0 && copy.bitmapHeight > 0){
            if(!copy.texture)
                glGenTextures(1, &copy.texture);

            glBindTexture(GL_TEXTURE_2D, copy.texture);
            glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(copy.bitmapFormat),
                            copy.pixelsWidth,
                            copy.pixelsWidth,
                            0, static_cast<GLenum>(copy.bitmapFormat),
                            GL_UNSIGNED_BYTE, copy.pixels);
        }
    }

    return in;
}

SpriteBase::SpriteBase():
   texture(0),
	bitmapWidth(0),
    bitmapHeight(0),
    pixelsWidth(0),
    pixels(NULL),
    bitmapFormat(Image::RGBA),
    bitmapBits(0),
	src_rect(0,0,0,0),
	show(true),
	x(0),y(0),z(0),
	zoom_x(1.0),zoom_y(1.0),
	angle_x(0),
	angle_y(0),
	angle_z(0),
	blend_type(BlendType::normal),
	flippedH(false),
    flippedV(false)
{
	for (uint8 i = 0; i < 4;++i)
        this->vColor[i].set(255,255,255,255);
}

SpriteBase::SpriteBase(const Bitmap* bitmap):
    texture(0),
	bitmapWidth(0),
    bitmapHeight(0),
    pixelsWidth(0),
    pixels(NULL),
    bitmapFormat(Image::RGBA),
    bitmapBits(0),
	src_rect(0,0,0,0),
	show(true),
	x(0),y(0),z(0),
	zoom_x(1.0),zoom_y(1.0),
	angle_x(0),
	angle_y(0),
	angle_z(0),
	blend_type(BlendType::normal),
	flippedH(false),
    flippedV(false)
{

	for (uint8 i = 0; i < 4;++i)
        vColor[i].set(255,255,255,255);

    this->setBitmap(bitmap);
}

void SpriteBase::setBitmap(const Bitmap* bitmap){
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
            glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(this->bitmapFormat),
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
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(this->bitmapFormat),
                        0,
                        0,
                        0, static_cast<GLenum>(this->bitmapFormat),
                        GL_UNSIGNED_BYTE, NULL);
}

void SpriteBase::copyProperties(const SpriteBase& copy){
    if(this != &copy){
        this->src_rect = copy.src_rect;
        this->show = copy.show;
        this->x = copy.x;
        this->y = copy.y;
        this->z = copy.z;
        this->zoom_x = copy.zoom_x;
        this->zoom_y = copy.zoom_y;
        this->angle_x = copy.angle_x;
        this->angle_y = copy.angle_y;
        this->angle_z = copy.angle_z;
        this->blend_type = copy.blend_type;
        this->flippedH = copy.flippedH;
        this->flippedV = copy.flippedV;
        for (uint8 i = 0; i < 4;++i)
            this->vColor[i] = copy.vColor[i];
    }
}

void SpriteBase::setRed(uint8 red){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].red = red;
}
void SpriteBase::setGreen(uint8 green){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].green = green;
}
void SpriteBase::setBlue(uint8 blue){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].blue = blue;
}
void SpriteBase::setAlpha(uint8 alpha){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].alpha = alpha;
}

void SpriteBase::setColor(const Color& color){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i] = color;
}
void SpriteBase::setColor(uint8 red,uint8 green,uint8 blue,uint8 alpha){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].set(red,green,blue,alpha);
}
void SpriteBase::setColor(uint8 red,uint8 green,uint8 blue){
    for (uint8 i = 0; i < 4;++i)
        this->vColor[i].set(red,green,blue);
}

uint SpriteBase::getTexWidth() const {return this->bitmapWidth;}
uint SpriteBase::getTexHeight() const {return this->bitmapHeight;}
uint SpriteBase::getTexBits() const {return this->bitmapBits;}
Image::DataFormat SpriteBase::getTexDataFormat() const {return this->bitmapFormat;}

GLuint SpriteBase::getTexture() const {return this->texture;}

};

