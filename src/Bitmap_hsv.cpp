#include <Fantasy2C/Bitmap.hpp>

namespace F2C{

void Bitmap::setHue(uint hue){
	if (! this->pixels)
			return;
	hue = hue % 360; //hue maximal 0-360

	ubyte rgb[3] = {0,0,0};
	int hsv[3] = {0,0,0};
	GLubyte* dstpixels = this->pixels;
	uint bpp = this->getBytes();

	for (uint y = 0 ; y < this->height ; y++ ){
		for (uint x = 0 ; x < this->width ; x++ ){
		    size_t dpi = (x + y * this->po2_size)*bpp;
            Color::RGBtoHSV(dstpixels[dpi],
                            dstpixels[dpi+1],
                            dstpixels[dpi+2],hsv);
            Color::HSVtoRGB(hue,hsv[1],hsv[2],rgb);
            memcpy(dstpixels+dpi,rgb,3*sizeof(ubyte));
        }
    }
    this->is_changed = true;
}

void Bitmap::setSaturation(uint8 s){
	if (! this->pixels)
			return;

	ubyte rgb[3] = {0,0,0};
	int hsv[3] = {0,0,0};
	GLubyte* dstpixels = this->pixels;
    uint bpp = this->getBytes();

	for (uint y = 0 ; y < this->height ; y++ ){
		for (uint x = 0 ; x < this->width ; x++ ){
            size_t dpi = (x + y * this->po2_size)*bpp;
            Color::RGBtoHSV(dstpixels[dpi],
                            dstpixels[dpi+1],
                            dstpixels[dpi+2],hsv);
            Color::HSVtoRGB(hsv[0],s,hsv[2],rgb);
            memcpy(dstpixels+dpi,rgb,3*sizeof(ubyte));
        }
    }
    this->is_changed = true;
}

void Bitmap::setValue(uint8 v){
	if (! this->pixels)
			return;

	ubyte rgb[3] = {0,0,0};
	int hsv[3] = {0,0,0};
	GLubyte* dstpixels = this->pixels;
    uint bpp = this->getBytes();

	for (uint y = 0 ; y < this->height ; y++ ){
		for (uint x = 0 ; x < this->width ; x++ ){
            size_t dpi = (x + y * this->po2_size)*bpp;
            Color::RGBtoHSV(dstpixels[dpi],
                            dstpixels[dpi+1],
                            dstpixels[dpi+2],hsv);
            Color::HSVtoRGB(hsv[0],hsv[1],v,rgb);
            memcpy(dstpixels+dpi,rgb,3*sizeof(ubyte));
        }
    }
    this->is_changed = true;
}

}

