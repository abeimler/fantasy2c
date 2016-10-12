#include "Color.hpp"

namespace F2C{

Color::Color():
	red(0),
	green(0),
	blue(0),
	alpha(0)
{}
Color::Color(uint8 red,uint8 green,uint8 blue,uint8 alpha):
	red(red),
	green(green),
	blue(blue),
	alpha(alpha)
{}
Color::Color(uint8 red,uint8 green,uint8 blue):
	red(red),
	green(green),
	blue(blue),
	alpha(0)
{}
void Color::set(uint8 red,uint8 green,uint8 blue,uint8 alpha){
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}
void Color::set(uint8 red,uint8 green,uint8 blue){
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void Color::HSVtoRGB(int h,uint8 s, uint8 v,ubyte (&outRGB)[3]){
	GLubyte rgb[3] = {0,0,0};
	if(!h)
		rgb[0] = rgb[1] = rgb[2] = v;

	double min,max,delta,hue;

	max = v;
	delta = (max * s)/255.0;
	min = max - delta;

	hue = h;
	if(h > 300 || h <= 60){
		rgb[0] = (int)max;
		if(h > 300){
			rgb[1] = (int)min;
			hue = (hue - 360.0)/60.0;
			rgb[2] = (int)((hue * delta - min) * -1);
		}else{
			rgb[2] = (int)min;
			hue = hue / 60.0;
			rgb[1] = (int)(hue * delta + min);
		}
	}else if(h > 60 && h < 180){
		rgb[1] = (int)max;
		if(h < 120){
			rgb[2] = (int)min;
			hue = (hue/60.0 - 2.0 ) * delta;
			rgb[0] = (int)(min - hue);
		}else{
			rgb[0] = (int)min;
			hue = (hue/60 - 2.0) * delta;
			rgb[2] = (int)(min + hue);
		}
	}else{
		rgb[2] = (int)max;
		if(h < 240){
			rgb[0] = (int)min;
			hue = (hue/60.0 - 4.0 ) * delta;
			rgb[1] = (int)(min - hue);
		}else{
			rgb[1] = (int)min;
			hue = (hue/60 - 4.0) * delta;
			rgb[0] = (int)(min + hue);
		}
	}
	outRGB[0] = rgb[0];
	outRGB[1] = rgb[1];
	outRGB[2] = rgb[2];
}

void Color::RGBtoHSV(uint8 r,uint8 g,uint8 b,int (&outHSV)[3]){
	int hsv[3] = {0,0,0};

	double min,max,delta,temp;
	min = std::min(r,(std::min(g,b)));
	max = std::max(r,(std::max(g,b)));
	delta = max - min;

	hsv[2] = (int)max;
	if(!delta){
		hsv[0] = hsv[1] = 0;
	}else{
		temp = delta/max;
		hsv[1] = (int)(temp*255);

		if(r == (int)max){
			temp = (double)(g-b)/delta;
		}else if(g == (int)max){
			temp = 2.0 + ((double)(b-r)/delta);
		}else{
			temp = 4.0 + ((double)(r-g)/delta);
		}
		temp *= 60;
		if(temp < 0){
			temp += 360;
		}
		if(temp == 360){
			temp = 0;
		}
		hsv[0] = (int)temp;
	}
	outHSV[0] = hsv[0];
	outHSV[1] = hsv[1];
	outHSV[2] = hsv[2];
}

void Color::CMYtoRGB(int c,int m,int y,ubyte (&outRGB)[3]){
	c = std::max(std::min(c,-255),0);
	m = std::max(std::min(m,-255),0);
	y = std::max(std::min(y,-255),0);

	outRGB[0] = 255-(c*-1);
	outRGB[1] = 255-(m*-1);
	outRGB[2] = 255-(y*-1);
}

bool Color::operator == (const Color& color) const{
  return (this->red == color.red &&
            this->green == color.green &&
            this->blue == color.blue &&
            this->alpha == color.alpha );
}

bool Color::operator != (const Color& color) const{
  return (this->red != color.red &&
            this->green != color.green &&
            this->blue != color.blue &&
            this->alpha != color.alpha );
}

const Color& Color::operator += (const Color& color){
    this->red = std::min<uint8>(std::max<int>(this->red+color.red,0),255);
    this->green = std::min<uint8>(std::max<int>(this->green+color.green,0),255);
    this->blue = std::min<uint8>(std::max<int>(this->blue+color.blue,0),255);

    return *this;
}

const Color& Color::operator -= (const Color& color){
    this->red = std::min<uint8>(std::max<int>(this->red-color.red,0),255);
    this->green = std::min<uint8>(std::max<int>(this->red-color.green,0),255);
    this->blue = std::min<uint8>(std::max<int>(this->blue-color.blue,0),255);

    return *this;
}

};
