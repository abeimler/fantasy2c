#include <Fantasy2C/Rect.hpp>

namespace F2C{

Rect::Rect():
	x(0),y(0),
	width(0),height(0)
{}

Rect::Rect(int x,int y,uint width,uint height):
		x(x),y(y),
		width(width),height(height)
{}

void Rect::set(int x,int y,uint width,uint height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

};

