#include <Fantasy2C/Color.hpp>

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

Color::Color(uint32 rgba):
	red(rgba >> 24),
	green(rgba >> 16),
	blue(rgba >> 8),
	alpha(rgba >> 0)
{}

uint32 Color::getUint32() const{
    return ((this->red << 24) | (this->green << 16) | (this->blue << 8)  | (this->alpha << 0));
}

Color::operator uint32 () const{
    return this->getUint32();
}

void Color::HSVtoRGB(int h,uint8 s, uint8 v,ubyte* outRGB){
    if(!outRGB)
        return;

    h = h % 360; //hue maximal 0-360

	GLubyte rgb[3] = {0};
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

void Color::RGBtoHSV(uint8 r,uint8 g,uint8 b,int* outHSV){
    if(!outHSV)
        return;

	int hsv[3] = {0};

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

void Color::CMYtoRGB(int c,int m,int y,ubyte* outRGB){
    if(!outRGB)
        return;

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

bool Color::operator < (const Color& color) const{
  return (this->red < color.red &&
            this->green < color.green &&
            this->blue < color.blue &&
            this->alpha < color.alpha );
}

bool Color::operator != (const Color& color) const{
  return !(*this == color);
}

const Color& Color::operator += (const Color& color){
    this->red = vclamp(static_cast<int>(this->red)+color.red,0,255);
    this->green = vclamp(static_cast<int>(this->green)+color.green,0,255);
    this->blue = vclamp(static_cast<int>(this->blue)+color.blue,0,255);
    this->alpha = vclamp(static_cast<int>(this->alpha)+color.alpha,0,255);

    return *this;
}

const Color& Color::operator -= (const Color& color){
    this->red = vclamp(static_cast<int>(this->red)-color.red,0,255);
    this->green = vclamp(static_cast<int>(this->green)-color.green,0,255);
    this->blue = vclamp(static_cast<int>(this->blue)-color.blue,0,255);
    this->alpha = vclamp(static_cast<int>(this->alpha)-color.alpha,0,255);

    return *this;
}

const Color& Color::operator *= (const Color& color){
    this->red = vclamp(static_cast<int>(this->red)*color.red,0,255);
    this->green = vclamp(static_cast<int>(this->green)*color.green,0,255);
    this->blue = vclamp(static_cast<int>(this->blue)*color.blue,0,255);
    this->alpha = vclamp(static_cast<int>(this->alpha)*color.alpha,0,255);

    return *this;
}

const Color& Color::operator /= (const Color& color){
    this->red = vclamp(static_cast<int>(this->red)/color.red,0,255);
    this->green = vclamp(static_cast<int>(this->green)/color.green,0,255);
    this->blue = vclamp(static_cast<int>(this->blue)/color.blue,0,255);
    this->alpha = vclamp(static_cast<int>(this->alpha)/color.alpha,0,255);

    return *this;
}

const Color& Color::operator += (uint8 col){
    Color color (col,col,col,col);
    *this += color;

    return *this;
}

const Color& Color::operator -= (uint8 col){
    Color color (col,col,col,col);
    *this -= color;

    return *this;
}

const Color& Color::operator *= (uint8 col){
    Color color (col,col,col,col);
    *this *= color;

    return *this;
}

const Color& Color::operator /= (uint8 col){
    Color color (col,col,col,col);
    *this /= color;

    return *this;
}

const Color& Color::operator *= (float col){
    this->red = vclamp<int>(this->red*col,0,255);
    this->green = vclamp<int>(this->green*col,0,255);
    this->blue = vclamp<int>(this->blue*col,0,255);
    this->alpha = vclamp<int>(this->alpha*col,0,255);

    return *this;
}

const Color& Color::operator /= (float col){
    this->red = vclamp<int>(this->red/col,0,255);
    this->green = vclamp<int>(this->green/col,0,255);
    this->blue = vclamp<int>(this->blue/col,0,255);
    this->alpha = vclamp<int>(this->alpha/col,0,255);

    return *this;
}

const Color& Color::operator *= (double col){
    this->red = vclamp<int>(this->red*col,0,255);
    this->green = vclamp<int>(this->green*col,0,255);
    this->blue = vclamp<int>(this->blue*col,0,255);
    this->alpha = vclamp<int>(this->alpha*col,0,255);

    return *this;
}

const Color& Color::operator /= (double col){
    this->red = vclamp<int>(this->red/col,0,255);
    this->green = vclamp<int>(this->green/col,0,255);
    this->blue = vclamp<int>(this->blue/col,0,255);
    this->alpha = vclamp<int>(this->alpha/col,0,255);

    return *this;
}

Color operator+(const Color& obj1,const Color& obj2){
    Color re = obj1;
    re += obj2;
    return re;
}
Color operator-(const Color& obj1,const Color& obj2){
    Color re = obj1;
    re -= obj2;
    return re;
}

Color operator*(const Color& obj1,const Color& obj2){
    Color re = obj1;
    re *= obj2;
    return re;
}
Color operator/(const Color& obj1,const Color& obj2){
    Color re = obj1;
    re /= obj2;
    return re;
}

Color operator+(const Color& obj1,uint8 col){
    Color re = obj1;
    re += col;
    return re;
}

Color operator-(const Color& obj1,uint8 col){
    Color re = obj1;
    re -= col;
    return re;
}

Color operator*(const Color& obj1,uint8 col){
    Color re = obj1;
    re *= col;
    return re;
}

Color operator/(const Color& obj1,uint8 col){
    Color re = obj1;
    re /= col;
    return re;
}

Color operator*(const Color& obj1,float col){
    Color re = obj1;
    re *= col;
    return re;
}

Color operator/(const Color& obj1,float col){
    Color re = obj1;
    re /= col;
    return re;
}

Color operator*(const Color& obj1,double col){
    Color re = obj1;
    re *= col;
    return re;
}

Color operator/(const Color& obj1,double col){
    Color re = obj1;
    re /= col;
    return re;
}

std::ostream& operator<<(std::ostream &out,const Color& obj){
    out << obj.red;
	out << obj.green;
	out << obj.blue;
	out << obj.alpha;

	return out;
}

std::istream& operator>>(std::istream &in, Color& obj){
    in >> obj.red;
	in >> obj.green;
	in >> obj.blue;
	in >> obj.alpha;

	return in;
}

}
