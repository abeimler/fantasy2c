#include "Bitmap.hpp"

namespace F2C{

void Bitmap::clear(){
	if (! this->pixels)
		return;
	memset(this->pixels,0,this->psize*sizeof(GLubyte));
}

void Bitmap::blt(const Bitmap& _Src,int _destX, int _destY, int _srcX,int _srcY, uint _width, uint _height){
	if (! this->pixels)
		return;

    _width = std::min(this->width,_destX+_width);
    _height = std::min(this->height,_destY+_height);

	this->blt_image(_Src.getPixels(),
                    _srcX,_srcY,
                    _Src.getPixelsWidth(),
                    _Src.getPixelsWidth(),
                    _Src.getBits() >> 3, //bits >> 3 = bits / 8,  (32 >> 3 = 4) bx0010 0000 >> 3 = bx0000 0100

                    this->pixels,
                    _destX, _destY,
                    this->po2_size,
                    this->po2_size,
                    this->bits >> 3,

                    _width,_height,true, 255);

}

void Bitmap::bltFull(const Bitmap& _Src,int _destX, int _destY){
    this->blt(_Src,_destX,_destY,0,0,_Src.getWidth(), _Src.getHeight());
}

void Bitmap::blt(const Bitmap& _Src,int _destX, int _destY, int _srcX,int _srcY, uint _width, uint _height,uint8 _alpha){
	if (! this->pixels)
		return;

    _width = std::min(this->width,_destX+_width);
    _height = std::min(this->height,_destY+_height);

	this->blt_image(_Src.getPixels(),
                    _srcX,_srcY,
                    _Src.getPixelsWidth(),
                    _Src.getPixelsWidth(),
                    _Src.getBits() >> 3, //bits >> 3 = bits / 8,  (32 >> 3 = 4) bx0010 0000 >> 3 = bx0000 0100

                    this->pixels,
                    _destX, _destY,
                    this->po2_size,
                    this->po2_size,
                    this->bits >> 3,

                    _width,_height,true, _alpha);

}

void Bitmap::bltFull(const Bitmap& _Src,int _destX, int _destY,uint8 _alpha){
	this->blt(_Src,_destX,_destY,0,0,_Src.getWidth(), _Src.getHeight(),_alpha);
}

void Bitmap::scale(uint _width,uint _height){
	if (! this->pixels)
		return;

    if(this->width == _width && this->height == _height)
        return;

    //Soure normal Pixel
	GLubyte* _srcnewpixels = new ubyte[this->width * this->height * (this->bits >> 3)];
    //Destination normal Pixels
	GLubyte* _dstnewpixels = new ubyte[_width * _height * (this->bits >> 3)];

    //byte per Pixel
    uint bpp = this->bits >> 3; //bits >> 3 = bits / 8,  (32 >> 3 = 4) bx0010 0000 >> 3 = bx0000 0100

    //copy power of two Pixels into normal size Pixels
    for(size_t x = 0;x < this->width;x++){
        for(size_t y = 0;y < this->height;y++){
            memcpy(&_srcnewpixels[(x + y * this->width)*bpp],
                    &this->pixels[(x + y * this->po2_size)*bpp],
                    bpp*sizeof(ubyte));
        }
    }
    //scale normal size Pixels (into _dstnewpixels)
	gluScaleImage(static_cast<GLenum>(this->data_format),
                    this->width,this->height,
                    GL_UNSIGNED_BYTE,
                    _srcnewpixels,
                    _width,_height,
                    GL_UNSIGNED_BYTE, _dstnewpixels);

    //create new power of two Pixels
    if (this->pixels)
      delete[] this->pixels;
    this->width = _width;
	this->height = _height;
	this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
    this->psize = this->po2_size * this->po2_size * bpp;
    this->pixels = new ubyte[this->psize];
    memset(this->pixels,0,this->psize);

    //copy normal size Pixels into power of two Pixels
    for(size_t x = 0;x < _width;x++){
        for(size_t y = 0;y < _height;y++){
            memcpy(&this->pixels[(x + y * this->po2_size)*bpp],
                    &_dstnewpixels[(x + y * _width)*bpp],
                    bpp*sizeof(ubyte));
        }
    }

    delete[] _srcnewpixels;
    delete[] _dstnewpixels;
}

void Bitmap::fillRect(int _x,int _y,uint _width,uint _height,uint8 r,uint8 g,uint8 b,uint8 a){
	if (! this->pixels)
		return;

	uint left    = std::max<uint>(_y, 0);
    uint top     = std::max<uint>(_x, 0);
    uint right   = std::min<uint>(left + _height, this->height);
    uint bottom  = std::min<uint>(top + _width, this->width);

    //byte per Pixel
    size_t bpp = this->bits >> 3;

    for (size_t y = left; y < right; y++){
        for (size_t x = top; x < bottom; x++){
            //Pixel index
            size_t pi = (x + y * this->po2_size)*bpp;
            GLubyte* dst = &this->pixels[pi];
            //Alpha Blending
            //src_color * alpha + dst_color * (255-alpha)
            //... >> 8 ,Keep in 0-255 Range
            if(bpp >= 4 && *(dst+3) > 0 && *(dst+3) < 255){
                *dst = ((r * (a+1)) + ((*dst) * (256-a))) >> 8;
                *(dst+1) = ((g * (a+1)) + ((*(dst+1)) * (256-a))) >> 8;
                *(dst+2) = ((b * (a+1)) + ((*(dst+2)) * (256-a))) >> 8;
                *(dst+3) = ((a * (a+1)) + ((*(dst+3)) * (256-a))) >> 8;
            }else{
                *dst = r;
                *(dst+1) = g;
                *(dst+2) = b;
                *(dst+3) = a;
            }
        }
    }
}

void Bitmap::fillRect(const Rect& rect,const Color& color){
	this->fillRect(rect.x,rect.y,rect.width,rect.height,color.red,color.green,color.blue,color.alpha);
}

void Bitmap::setPixel(uint x,uint y, uint8 r,uint8 g,uint8 b,uint8 a){
	if (! this->pixels)
		return;

	if (x < 0 || y < 0 || x > this->width || y > this->height)
        return;

    //byte per Pixel
    size_t bpp = this->bits >> 3;

    //start Pixel index
    size_t pi = (x + y * this->po2_size)*bpp;

    this->pixels[pi] = r;
    this->pixels[1+pi] = g;
    this->pixels[2+pi] = b;
    if(bpp >= 4)
        this->pixels[3+pi] = a;
}

void Bitmap::setPixel(uint x,uint y, Color color){
	this->setPixel(x,y,color.red,color.green,color.blue,color.alpha);
}

Color Bitmap::getPixel(uint x,uint y) const{
	Color reColor;
	if (! this->pixels)
		return reColor;

	if(x > width || y > height)
		return reColor;

    //byte per Pixel
    size_t bpp = this->bits >> 3;

    //Pixel index
    size_t pi = (x + y * this->po2_size)*bpp;

    reColor.set(this->pixels[pi],
                this->pixels[pi+1],
                this->pixels[pi+2],
                (bpp >= 4)? this->pixels[pi+3] : 255);

	return reColor;
}


void Bitmap::save(std::string _filename) const{
	if (! this->pixels)
			return;
	GLuint _image;
	ilGenImages(1,&_image);
	ilBindImage(_image);

    //copy power of two Pixels into normal size Pixels
	ubyte* _srcpixels = new ubyte[this->width * this->height * (this->bits/8)];
    size_t bpp = this->bits >> 3;
    for(size_t x = 0;x < this->width;x++){
        for(size_t y = 0;y < this->height;y++){
            memcpy(&_srcpixels[(x + y * this->width)*bpp],
                    &this->pixels[(x + y * this->po2_size)*bpp],
                    bpp*sizeof(ubyte));
        }
    }

	ilTexImage(this->width,this->height,1,this->bits >> 3,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,_srcpixels);
	ilSaveImage(_filename.c_str());
	ilDeleteImages(1,&_image);
	delete[] _srcpixels;
}

void Bitmap::save(std::string _filename,Image::ImageType _type) const{
	if (! this->pixels)
			return;
	GLuint _image;
	ilGenImages(1,&_image);
	ilBindImage(_image);

    //copy power of two Pixels into normal size Pixels
	ubyte* _srcpixels = new ubyte[this->width * this->height * (this->bits >> 3)];
    size_t bpp = this->bits >> 3;
    for(size_t x = 0;x < this->width;x++){
        for(size_t y = 0;y < this->height;y++){
            memcpy(&_srcpixels[(x + y * this->width)*bpp],
                    &this->pixels[(x + y * this->po2_size)*bpp],
                    bpp*sizeof(ubyte));
        }
    }

	ilTexImage(this->width,this->height,1,this->bits >> 3,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,_srcpixels);
	ilSave(_type,const_cast<char*>(_filename.c_str()));
	ilDeleteImages(1,&_image);
	delete[] _srcpixels;
}

const ubyte* Bitmap::getPixels() const {return this->pixels;}
ubyte* Bitmap::getPixels() {return this->pixels;}
std::string Bitmap::getFilename() const {return this->filename;}
uint Bitmap::getWidth() const {return this->width;}
uint Bitmap::getHeight() const {return this->height;}
uint Bitmap::getCreateWidth() const {return this->create_width;}
uint Bitmap::getCreateHeight() const {return this->create_height;}
Image::ImageType Bitmap::getImageType() const
                                    {return static_cast<Image::ImageType>(this->image_type);}
Image::DataFormat Bitmap::getDataFormat() const
                                    {return static_cast<Image::DataFormat>(this->data_format);}
uint Bitmap::getBits() const {return this->bits;}
Rect Bitmap::getRect() const {return Rect (0,0,this->getWidth(),this->getHeight());}
uint32 Bitmap::getPixelsSize() const {return this->psize;}
uint Bitmap::getPixelsWidth() const {return this->po2_size;}

};
