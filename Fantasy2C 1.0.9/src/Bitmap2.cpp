#include "Bitmap.hpp"

namespace F2C{

void Bitmap::setHue(uint hue){
	if (! this->pixels)
			return;
	hue = hue % 360; //hue maximal 0-360

	ubyte rgb[3] = {0,0,0};
	int hsv[3] = {0,0,0};
	GLubyte* dstpixels = this->pixels;
	uint bpp = this->bits >> 3;

	for (uint y = 0 ; y < this->height ; y++ ){
		for (uint x = 0 ; x < this->width ; x++ ){
            Color::RGBtoHSV(dstpixels[bpp*(x + y * this->po2_size)],
                            dstpixels[bpp*(x + y * this->po2_size)+1],
                            dstpixels[bpp*(x + y * this->po2_size)+2],hsv);
            Color::HSVtoRGB(hue,hsv[1],hsv[2],rgb);
            memcpy(&dstpixels[bpp*(x + y * this->po2_size)],&rgb,3*sizeof(ubyte));
        }
    }
}

void Bitmap::setSaturation(uint8 s){
	if (! this->pixels)
			return;

	ubyte rgb[3] = {0,0,0};
	int hsv[3] = {0,0,0};
	GLubyte* dstpixels = this->pixels;
    uint bpp = this->bits >> 3;

	for (uint y = 0 ; y < this->height ; y++ ){
		for (uint x = 0 ; x < this->width ; x++ ){
            Color::RGBtoHSV(dstpixels[bpp*(x + y * this->po2_size)],
                            dstpixels[bpp*(x + y * this->po2_size)+1],
                            dstpixels[bpp*(x + y * this->po2_size)+2],hsv);
            Color::HSVtoRGB(hsv[0],s,hsv[2],rgb);
            memcpy(&dstpixels[bpp*(x + y * this->po2_size)],&rgb,3*sizeof(ubyte));
        }
    }
}

void Bitmap::setValue(uint8 v){
	if (! this->pixels)
			return;

	ubyte rgb[3] = {0,0,0};
	int hsv[3] = {0,0,0};
	GLubyte* dstpixels = this->pixels;
    uint bpp = this->bits >> 3;

	for (uint y = 0 ; y < this->height ; y++ ){
		for (uint x = 0 ; x < this->width ; x++ ){
            Color::RGBtoHSV(dstpixels[bpp*(x + y * this->po2_size)],
                            dstpixels[bpp*(x + y * this->po2_size)+1],
                            dstpixels[bpp*(x + y * this->po2_size)+2],hsv);
            Color::HSVtoRGB(hsv[0],hsv[1],v,rgb);
            memcpy(&dstpixels[bpp*(x + y * this->po2_size)],&rgb,3*sizeof(ubyte));
        }
    }
}

};

