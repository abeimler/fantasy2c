#include <Fantasy2C/ColorTone.hpp>

namespace F2C{

ColorTone::ColorTone():
	red(0),
	green(0),
	blue(0),
	grayscale(0)
{}

ColorTone::ColorTone(int16 red,int16 green,int16 blue,uint8 grayscale):
    red(red),
	green(green),
	blue(blue),
	grayscale(grayscale)
{
	if( this->red > 255 )
    { this->red = 255;}
    else if( this->red < -255 )
    {this->red = -255;}

    if( this->green > 255 )
    { this->green = 255;}
    else if( this->green < -255 )
    {this->green = -255;}

    if( this->blue > 255 )
    { this->blue = 255;}
    else if( this->blue < -255 )
    {this->blue = -255;}
}

ColorTone::ColorTone(int16 red,int16 green,int16 blue):
    red(red),
	green(green),
	blue(blue),
	grayscale(0)
{
    if( this->red > 255 )
    { this->red = 255;}
    else if( this->red < -255 )
    {this->red = -255;}

    if( this->green > 255 )
    { this->green = 255;}
    else if( this->green < -255 )
    {this->green = -255;}

    if( this->blue > 255 )
    { this->blue = 255;}
    else if( this->blue < -255 )
    {this->blue = -255;}
}
void ColorTone::set(int16 red,int16 green,int16 blue,uint8 grayscale){
	this->grayscale = grayscale;
	this->red = red;
    this->green = green;
    this->blue = blue;

	if( this->red > 255 )
    { this->red = 255;}
    else if( this->red < -255 )
    {this->red = -255;}

    if( this->green > 255 )
    { this->green = 255;}
    else if( this->green < -255 )
    {this->green = -255;}

    if( this->blue > 255 )
    { this->blue = 255;}
    else if( this->blue < -255 )
    {this->blue = -255;}
}
void ColorTone::set(int16 red,int16 green,int16 blue){
    this->red = red;
    this->green = green;
    this->blue = blue;

	if( this->red > 255 )
    { this->red = 255;}
    else if( this->red < -255 )
    {this->red = -255;}

    if( this->green > 255 )
    { this->green = 255;}
    else if( this->green < -255 )
    {this->green = -255;}

    if( this->blue > 255 )
    { this->blue = 255;}
    else if( this->blue < -255 )
    {this->blue = -255;}
}

void ColorTone::set(const Color& color){
    this->set(color.red,color.green,color.blue);
}

void ColorTone::setRed(int16 red){
    this->red = red;

	if( this->red > 255 )
    { this->red = 255;}
    else if( this->red < -255 )
    {this->red = -255;}
}

void ColorTone::setGreen(int16 green){
    this->green = green;

    if( this->green > 255 )
    { this->green = 255;}
    else if( this->green < -255 )
    {this->green = -255;}
}

void ColorTone::setBlue(int16 blue){
    this->blue = blue;

    if( this->blue > 255 )
    { this->blue = 255;}
    else if( this->blue < -255 )
    {this->blue = -255;}
}

void ColorTone::ColorTonetoHSV(const ColorTone& ctone,int (&hsv)[3]){
	ubyte rgb[3] = {0,0,0};
	if (ctone.red < 0)
		rgb[0] = static_cast<ubyte>(255+(ctone.red*-1));
	else
		rgb[0] = static_cast<ubyte>(ctone.red);

	if (ctone.green < 0)
		rgb[1] = static_cast<ubyte>(255+(ctone.green*-1));
	else
		rgb[1] = static_cast<ubyte>(ctone.green);

	if (ctone.blue < 0)
		rgb[2] = static_cast<ubyte>(255+(ctone.blue*-1));
	else
		rgb[2] = static_cast<ubyte>(ctone.blue);

	Color::RGBtoHSV(rgb[0],rgb[1],rgb[2],hsv);
}

void ColorTone::ColorTonetoRGB(const ColorTone& ctone,ubyte (&rgb)[3]){
	if (ctone.red < 0){
		rgb[1] = static_cast<ubyte>(ctone.red*-1);
		rgb[2] = static_cast<ubyte>(ctone.red*-1);
	}else
		rgb[0] = static_cast<ubyte>(ctone.red);

	if (ctone.green < 0){
		rgb[0] = static_cast<ubyte>(ctone.green*-1);
		rgb[2] = static_cast<ubyte>(ctone.green*-1);
	}else
		rgb[1] = static_cast<ubyte>(ctone.green);

	if (ctone.blue < 0){
		rgb[0] = static_cast<ubyte>(ctone.blue*-1);
		rgb[1] = static_cast<ubyte>(ctone.blue*-1);
	}else
		rgb[2] = static_cast<ubyte>(ctone.blue);

}

bool ColorTone::operator == (const ColorTone& color) const{
  return (this->red == color.red &&
            this->green == color.green &&
            this->blue == color.blue &&
            this->grayscale == color.grayscale );
}

bool ColorTone::operator != (const ColorTone& color) const{
  return (this->red != color.red &&
            this->green != color.green &&
            this->blue != color.blue &&
            this->grayscale != color.grayscale );
}

const ColorTone& ColorTone::operator += (const ColorTone& color){
    this->red += color.red;
    this->green += color.green;
    this->blue += color.blue;

    if( this->red > 255 )
    { this->red = 255;}
    else if( this->red < -255 )
    {this->red = -255;}

    if( this->green > 255 )
    { this->green = 255;}
    else if( this->green < -255 )
    {this->green = -255;}

    if( this->blue > 255 )
    { this->blue = 255;}
    else if( this->blue < -255 )
    {this->blue = -255;}

    this->grayscale += color.grayscale;
    return *this;
}

const ColorTone& ColorTone::operator -= (const ColorTone& color){
    this->red -= color.red;
    this->green -= color.green;
    this->blue -= color.blue;

    if( this->red > 255 )
    { this->red = 255;}
    else if( this->red < -255 )
    {this->red = -255;}

    if( this->green > 255 )
    { this->green = 255;}
    else if( this->green < -255 )
    {this->green = -255;}

    if( this->blue > 255 )
    { this->blue = 255;}
    else if( this->blue < -255 )
    {this->blue = -255;}
    this->grayscale -= color.grayscale;

    return *this;
}

int16 ColorTone::getRed() const {return this->red;}
int16 ColorTone::getGreen() const {return this->green;}
int16 ColorTone::getBlue() const {return this->blue;}

ColorTone operator+(const ColorTone& obj1,const ColorTone& obj2){
    ColorTone re = obj1;
    re += obj2;
    return re;
}
ColorTone operator-(const ColorTone& obj1,const ColorTone& obj2){
    ColorTone re = obj1;
    re -= obj2;
    return re;
}

std::ostream& operator<<(std::ostream &out,const ColorTone& obj){
    out << obj.red;
    out << obj.green;
    out << obj.blue;
    out << obj.grayscale;

    return out;
}

std::istream& operator>>(std::istream &in, ColorTone& obj){
    in >> obj.red;
    in >> obj.green;
    in >> obj.blue;
    in >> obj.grayscale;

    return in;
}

};

