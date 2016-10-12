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

bool Rect::collision(const Rect& rect) const {
    if(this->x+this->width < rect.x) return false;
    if(this->y+this->height < rect.y) return false;
    if(this->x > rect.x+rect.width) return false;
    if(this->y > rect.y+rect.height) return false;

    return true;
}

std::ostream& operator<<(std::ostream &out,const F2C::Rect& obj){
    out << obj.x;
	out << obj.y;
	out << obj.width;
	out << obj.height;

	return out;
}

std::istream& operator>>(std::istream &in, F2C::Rect& obj){
    in >> obj.x;
	in >> obj.y;
	in >> obj.width;
	in >> obj.height;

	return in;
}


Coord::Coord():
	x(0),y(0),z(0)
{}

Coord::Coord(int x,int y,int z):
		x(x),y(y),z(z)
{}

void Coord::set(int x,int y,int z){
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Coord::collision(const Coord& coord) const {
    return this->x == coord.x && this->y == coord.y && this->z == coord.z;
}

std::ostream& operator<<(std::ostream &out,const F2C::Coord& obj){
    out << obj.x;
	out << obj.y;
	out << obj.z;

	return out;
}

std::istream& operator>>(std::istream &in, F2C::Coord& obj){
    in >> obj.x;
	in >> obj.y;
	in >> obj.z;

	return in;
}

};
