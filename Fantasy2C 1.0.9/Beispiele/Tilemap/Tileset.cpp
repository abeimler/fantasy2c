#include "Tileset.hpp"

Tileset::Tileset():
    tileW(0),
    tileH(0),
    vtileW(0),
    vtileH(0)
{}

void Tileset::setBitmap(const F2C::Bitmap& bitmap, F2C::uint tileW, F2C::uint tileH){
    this->tileset = bitmap;
    this->tileW = tileW;
    this->tileH = tileH;
    this->tilecoord.clear();
    this->passable.clear();
    this->priorities.clear();
    if(tileW < 1 || tileH < 1)
        return;

    for(size_t x = 0;x < this->tileset.getWidth();x+=this->tileW)
        this->vtileW++;
    for(size_t y = 0;y < this->tileset.getHeight();y+=this->tileH)
        this->vtileH++;

    for(size_t y = 0;y < this->tileset.getHeight();y+=this->tileH){
        for(size_t x = 0;x < this->tileset.getWidth();x+=this->tileW){
            this->tilecoord.push_back(F2C::Rect (x,y,this->tileW,this->tileH));
            this->passable.push_back(true);
            this->priorities.push_back(0);
        }
    }
}

F2C::uint Tileset::getTileW() const{
    return this->tileW;
}
F2C::uint Tileset::getTileH() const{
    return this->tileH;
}

size_t Tileset::getSize() const{
    return this->tilecoord.size();
}

void Tileset::setPassable(F2C::uint id, bool value){
    if(id > this->passable.size() || this->passable.empty())
        return;

    this->passable[id] = value;
}

bool Tileset::getPassable(F2C::uint id) const{
    if(id > this->passable.size() || this->passable.empty())
        return false;

    return this->passable[id];
}

void Tileset::setPriorities(F2C::uint id, int value){
    if(id > this->priorities.size() || this->priorities.empty())
        return;

    this->priorities[id] = value;
}

int Tileset::getPriorities(F2C::uint id) const{
    if(id > this->priorities.size() || this->priorities.empty())
        return 0;

    return this->priorities[id];
}

size_t Tileset::getID(F2C::uint x,F2C::uint y) const{
    if(this->tilecoord.empty())
        return 0;
    if(x > this->vtileW || y > this->vtileH)
        return 0;

    return x+y*this->vtileW;
}

F2C::Rect Tileset::getTileCoord(F2C::uint id) const{
    if(id > this->tilecoord.size() || this->tilecoord.empty())
        return F2C::Rect ();

    return this->tilecoord[id];
}

const F2C::Bitmap& Tileset::getBitmap() const{
    return this->tileset;
}
