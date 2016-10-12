#include <Fantasy2C/Viewport.hpp>

namespace F2C{

Viewport::Viewport():
	clip_rect(0,0,0,0),
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

};

