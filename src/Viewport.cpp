#include <Fantasy2C/Viewport.hpp>

namespace F2C{

Viewport::Viewport():
	show(true),
	z(0)
{}

Viewport::Viewport(int x,int y,uint width,uint height):
	clip_rect(x,y,width,height),
	show(true),
	z(0)
{}

Viewport::Viewport(const Rect& rect):
	clip_rect(rect),
	show(true),
	z(0)
{}

std::ostream& operator<<(std::ostream &out, Viewport& obj){
    out << obj.clip_rect;
    out << obj.show;
    out << obj.z;
    out << obj.tone;

    return out;
}

std::istream& operator>>(std::istream &in, Viewport& obj){
    in >> obj.clip_rect;
    in >> obj.show;
    in >> obj.z;
    in >> obj.tone;

    return in;
}

};

