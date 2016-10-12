#include <Fantasy2C/Bitmap.hpp>

namespace F2C{

void Bitmap::clear(){
	if (! this->pixels)
		return;
	memset(this->pixels,0,this->psize*sizeof(ubyte));
	if(this->filename.empty())
        this->is_changed = true;
}

void Bitmap::blt(const Bitmap& _Src,int _destX, int _destY, int _srcX,int _srcY, uint _width, uint _height){
	if (! this->pixels || !_Src.getPixels())
		return;

	Bitmap::blt_image(_Src.getPixels(),
                    _srcX,_srcY,
                    _Src.getPixelsWidth(),
                    _Src.getBytes(),
                    _Src.getWidth(),_Src.getHeight(),

                    this->pixels,
                    _destX, _destY,
                    this->po2_size,
                    this->getBytes(),
                    this->width,this->height,

                    _width,_height,true, 255);

    this->is_changed = true;
}

void Bitmap::bltFull(const Bitmap& _Src,int _destX, int _destY){
    this->blt(_Src,_destX,_destY,0,0,_Src.getWidth(), _Src.getHeight());
}

void Bitmap::blt(const Bitmap& _Src,int _destX, int _destY, int _srcX,int _srcY, uint _width, uint _height,uint8 _alpha){
	if (! this->pixels || !_Src.getPixels())
		return;

	Bitmap::blt_image(_Src.getPixels(),
                    _srcX,_srcY,
                    _Src.getPixelsWidth(),
                    _Src.getBytes(), //bits >> 3 = bits / 8,  (32 >> 3 = 4) bx0010 0000 >> 3 = bx0000 0100
                    _Src.getWidth(),_Src.getHeight(),

                    this->pixels,
                    _destX, _destY,
                    this->po2_size,
                    this->getBytes(),
                    this->width,this->height,

                    _width,_height,true, _alpha);

    this->is_changed = true;

}

void Bitmap::bltFull(const Bitmap& _Src,int _destX, int _destY,uint8 _alpha){
	this->blt(_Src,_destX,_destY,0,0,_Src.getWidth(), _Src.getHeight(),_alpha);
}

void Bitmap::scale(uint _width,uint _height){
	if (! this->pixels)
		return;

    if(this->width == _width && this->height == _height)
        return;

    uint bpp = this->getBytes();

    //Source normal Pixel
	GLubyte* _srcnewpixels = new ubyte[this->width * this->height * bpp]();
    //Destination normal Pixels
	GLubyte* _dstnewpixels = new ubyte[_width * _height * bpp]();

    //copy power of two Pixels into normal size Pixels
    Bitmap::blt_image(this->pixels,
                        0, 0,this->po2_size,
                        bpp,
                        this->width,this->height,

                        _srcnewpixels,
                        0, 0,this->width,
                        bpp,
                        this->width,this->height,

                        this->width,this->height,
                        false,255);


    //scale normal size Pixels (into _dstnewpixels)
	gluScaleImage(static_cast<GLenum>(this->data_format),
                    this->width,this->height,
                    GL_UNSIGNED_BYTE,
                    _srcnewpixels,
                    _width,_height,
                    GL_UNSIGNED_BYTE, _dstnewpixels);

    //create new power of two Pixels
    this->width = _width;
	this->height = _height;
	this->po2_size = nextPowerof2(std::max<uint>(this->width,this->height));
    this->psize = this->po2_size * this->po2_size * bpp;
    if (this->pixels)
        delete[] this->pixels;
    this->pixels = new ubyte[this->psize]();

    //copy normal size Pixels into power of two Pixels
    Bitmap::blt_image(_dstnewpixels,
                        0, 0,_width,
                        bpp,
                        _width,_height,

                        this->pixels,
                        0, 0,this->po2_size,
                        bpp,
                        this->width,this->height,

                        _width ,_height,
                        false,255);

    delete[] _srcnewpixels;
    delete[] _dstnewpixels;

    this->is_changed = true;
}

void Bitmap::fillRect(int _x,int _y,uint _width,uint _height,uint8 r,uint8 g,uint8 b,uint8 a){
	if (! this->pixels)
		return;

	uint left    = std::max<uint>(_y, 0);
    uint top     = std::max<uint>(_x, 0);
    uint right   = std::min<uint>(left + _height, this->height);
    uint bottom  = std::min<uint>(top + _width, this->width);

    //byte per Pixel
    //size_t bpp = this->getBytes();

    //convert to array
    ubyte rgba[4] = {r,g,b,a};

    Bitmap fillBitmap (bottom,right);
    size_t filllen = fillBitmap.getPixelsSize();
    ubyte* fillPixels = fillBitmap.getPixels();
    int rgbai = 0;

    while (filllen-- > 0){
        *fillPixels++ = rgba[rgbai];
        rgbai = (rgbai+1) % 4;
    }

    Bitmap::blt_image(fillBitmap.getPixels(),
                    0,0,
                    fillBitmap.getPixelsWidth(),
                    fillBitmap.getBytes(),
                    fillBitmap.getWidth(),fillBitmap.getHeight(),

                    this->pixels,
                    top, left,
                    this->po2_size,
                    this->getBytes(),
                    this->width,this->height,

                    fillBitmap.getWidth(),fillBitmap.getHeight(),true, 255);


    this->is_changed = true;
}

void Bitmap::fillRect(const Rect& rect,const Color& color){
	this->fillRect(rect.x,rect.y,rect.width,rect.height,color.red,color.green,color.blue,color.alpha);
}

void Bitmap::clearRect(int _x,int _y,uint _width,uint _height,uint8 r,uint8 g,uint8 b,uint8 a){
	if (! this->pixels)
		return;

	uint left    = std::max<uint>(_y, 0);
    uint top     = std::max<uint>(_x, 0);
    uint right   = std::min<uint>(left + _height, this->height);
    uint bottom  = std::min<uint>(top + _width, this->width);

    //byte per Pixel
    //size_t bpp = this->getBytes();

    Bitmap fillBitmap (bottom,right);

    Bitmap::blt_image(fillBitmap.getPixels(),
                    0,0,
                    fillBitmap.getPixelsWidth(),
                    fillBitmap.getBytes(),
                    fillBitmap.getWidth(),fillBitmap.getHeight(),

                    this->pixels,
                    top, left,
                    this->po2_size,
                    this->getBytes(),
                    this->width,this->height,

                    fillBitmap.getWidth(),fillBitmap.getHeight(),false, 255);


    this->is_changed = true;
}

void Bitmap::clearRect(const Rect& rect,const Color& color){
	this->clearRect(rect.x,rect.y,rect.width,rect.height,color.red,color.green,color.blue,color.alpha);
}

void Bitmap::setPixel(uint x,uint y, uint8 r,uint8 g,uint8 b,uint8 a){
	if (! this->pixels)
		return;

	if (x < 0 || y < 0 || x > this->width || y > this->height)
        return;

    //byte per Pixel
    size_t bpp = this->getBytes();

    //start Pixel index
    uint32 pi = (x + y * this->po2_size)*bpp;

    this->pixels[pi] = r;
    this->pixels[1+pi] = g;
    this->pixels[2+pi] = b;
    if(bpp >= 4)
        this->pixels[3+pi] = a;

    this->is_changed = true;
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
    size_t bpp = this->getBytes();

    //Pixel index
    uint32 pi = (x + y * this->po2_size)*bpp;

    reColor.set(this->pixels[pi],
                this->pixels[pi+1],
                this->pixels[pi+2],
                (bpp >= 4)? this->pixels[pi+3] : 255);

	return reColor;
}


void Bitmap::save(std::string _filename) const{
	if (! this->pixels)
			return;
	GLuint _image = 0;
	ilGenImages(1,&_image);
	ilBindImage(_image);

	size_t bpp = this->getBytes();

    //copy power of two Pixels into normal size Pixels
	ubyte* _srcpixels = new ubyte[this->width * this->height * bpp];

    Bitmap::blt_image(this->pixels,
                        0, 0,this->po2_size,
                        bpp,
                        this->width,this->height,

                        _srcpixels,
                        0, 0,this->width,
                        bpp,
                        this->width,this->height,

                        this->width,this->height,
                        false,255);

	ilTexImage(this->width,this->height,1,bpp,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,_srcpixels);

	//bug?: is flipped by save
	ilSave(IL_TYPE_UNKNOWN,_filename.c_str());

	//load again
	Bitmap tmpbitmap (_filename);
	Bitmap::blt_image(tmpbitmap.getPixels(),
                        0, 0,tmpbitmap.getPixelsWidth(),
                        bpp,
                        tmpbitmap.getWidth(),tmpbitmap.getHeight(),

                        _srcpixels,
                        0, 0,this->width,
                        bpp,
                        this->width,this->height,

                        this->width,this->height,
                        false,255);

    ilTexImage(this->width,this->height,1,bpp,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,_srcpixels);

    //and save to flipped again
    ilSave(IL_TYPE_UNKNOWN,_filename.c_str());
	ilDeleteImages(1,&_image);
	delete[] _srcpixels;
}

void Bitmap::save(std::string _filename,Image::ImageType _type) const{
	if (! this->pixels)
			return;
	GLuint _image;
	ilGenImages(1,&_image);
	ilBindImage(_image);

    size_t bpp = this->getBytes();

    //copy power of two Pixels into normal size Pixels
	ubyte* _srcpixels = new ubyte[this->width * this->height * bpp];

    Bitmap::blt_image(this->pixels,
                        0, 0,this->po2_size,
                        bpp,
                        this->width,this->height,

                        _srcpixels,
                        0, 0,this->width,
                        bpp,
                        this->width,this->height,

                        this->width,this->height,
                        false,255);

	ilTexImage(this->width,this->height,1,bpp,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,_srcpixels);

	//bug?: is flipped by save
	ilSave(_type,_filename.c_str());

	//load again
	Bitmap tmpbitmap (_filename);
	Bitmap::blt_image(tmpbitmap.getPixels(),
                        0, 0,tmpbitmap.getPixelsWidth(),
                        bpp,
                        tmpbitmap.getWidth(),tmpbitmap.getHeight(),

                        _srcpixels,
                        0, 0,this->width,
                        bpp,
                        this->width,this->height,

                        this->width,this->height,
                        false,255);

    ilTexImage(this->width,this->height,1,bpp,static_cast<ILenum>(this->data_format),IL_UNSIGNED_BYTE,_srcpixels);

    //and save to flipped again
    ilSave(_type,_filename.c_str());

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
Image::ImageType Bitmap::getImageType() const {return this->image_type;}
Image::DataFormat Bitmap::getDataFormat() const {return this->data_format;}
uint Bitmap::getBits() const {return this->bits;}
uint Bitmap::getBytes() const {return this->bits >> 3;} //bits >> 3 = bits / 8,  (32 >> 3 = 4) bx0010 0000 >> 3 = bx0000 0100
Rect Bitmap::getRect() const {return Rect (0,0,this->getWidth(),this->getHeight());}
size_t Bitmap::getPixelsSize() const {return this->psize;}
uint Bitmap::getPixelsWidth() const {return this->po2_size;}
bool Bitmap::isChanged() const {return this->is_changed;}

};
