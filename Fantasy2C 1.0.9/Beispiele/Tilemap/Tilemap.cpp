#include "Tilemap.hpp"

void Tilemap::updateSpr(F2C::uint xx,F2C::uint yy,F2C::uint width,F2C::uint height){
    if(this->spr.elements.empty())
        return;

    size_t ei = 0; //current tile number
    width = std::min(xx+width,this->width);
    height = std::min(yy+height,this->height);
    for(size_t l = 0;l < this->layers;l++){
        for(size_t y = yy,ey = 0;y < height;y++,ey++){
            for(size_t x = xx,ex = 0;x < width;x++,ex++){
                //array[x][y][l] = array[i]
                size_t i = l+(x+y*this->width)*this->layers;

                if(i > this->ids.size())
                    break;
                size_t id = this->ids[i]; //get tilesetid
                //set Coord. and tile
                this->spr.elements[ei].x = ex*this->tileset.getTileW();
                this->spr.elements[ei].y = ey*this->tileset.getTileH();
                this->spr.elements[ei].z = this->tileset.getPriorities(id)*32;
                this->spr.elements[ei].src_rect = this->tileset.getTileCoord(id);
                ei++;
                if(ei > this->spr.elements.size()){
                    //delete last tiles (invisible tiles)
                    while(ei < this->spr.elements.size()){
                        this->spr.elements.pop_back();
                    }
                    return;
                }
            }
        }
    }

    //delete last tiles (invisible tiles)
    while(ei < this->spr.elements.size()){
        this->spr.elements.pop_back();
    }
}

Tilemap::Tilemap():
    width(0),height(0),layers(0),
    lasttileW(0),lasttileH(0),
    x(0),y(0),z(0),
    ox(0),oy(0)
{}

Tilemap::Tilemap(F2C::uint width, F2C::uint height,F2C::uint layers):
    width(width),height(height),layers(layers),
    lasttileW(0),lasttileH(0),
    x(0),y(0),z(0),
    ox(0),oy(0)
{
    if(this->width*this->height*this->layers < 1)
        return;

    this->ids.resize(this->width*this->height*this->layers);
    memset(&this->ids[0],0,this->ids.size()*sizeof(this->ids[0]));
}

void Tilemap::resize(F2C::uint width, F2C::uint height,F2C::uint layers){
    if(this->ids.empty()){
        this->width = width;
        this->height = height;
        this->layers = layers;
        this->ids.resize(this->width*this->height*this->layers);
        memset(&this->ids[0],0,this->ids.size()*sizeof(this->ids[0]));
        return;
    }
    if(width*height*layers < 1){
        this->ids.clear();
        return;
    }

    //copy of old tiles (ids,width,height,layers)
    std::vector<size_t> tmpids = this->ids;
    F2C::uint tmpwidth = this->width;
    F2C::uint tmpheight = this->height;
    F2C::uint tmplayers = this->layers;

    //resize and copy old tiles
    this->width = width;
    this->height = height;
    this->layers = layers;
    this->ids.resize(this->width*this->height*this->layers);
    for(size_t y = 0;y < this->height;y++){
        for(size_t x = 0;x < this->width;x++){
            for(size_t layer = 0;layer < this->layers;layer++){

                if(x < tmpwidth && y < tmpheight && layer < tmplayers)
                    this->ids[layer+(x+y*this->width)*this->layers] = tmpids[layer+(x+y*tmpwidth)*tmplayers];
                else
                    this->ids[layer+(x+y*this->width)*this->layers] = 0;

            }
        }
    }

    this->width = width;
    this->height = height;
    this->layers = layers;
}

void Tilemap::setTileset(const Tileset& tileset){
    this->tileset = tileset;
    this->spr.setBitmap(&this->tileset.getBitmap());
}
const Tileset& Tilemap::getTileset() const{
    return this->tileset;
}
void Tilemap::setID(F2C::uint x,F2C::uint y,F2C::uint layer,F2C::uint id){
    if(x > this->width || y > this->height || layer > this->layers)
        return;

    this->ids[layer+(x+y*this->width)*this->layers] = id;
}
F2C::uint Tilemap::getID(F2C::uint x,F2C::uint y,F2C::uint layer) const{
    if(x >= this->width || y >= this->height || layer >= this->layers)
        return 0;
    return this->ids[layer+(x+y*this->width)*this->layers];
}

bool Tilemap::getPassable(F2C::uint x,F2C::uint y,F2C::uint layer) const{
    if(x >= this->width || y >= this->height || layer >= this->layers)
        return false;

    return this->tileset.getPassable(this->ids[layer+(x+y*this->width)*this->layers]);
}
bool Tilemap::getPassable(F2C::uint x,F2C::uint y) const{
    if(x >= this->width || y >= this->height)
        return false;

    bool re = false;
    for(size_t l = 0;l < this->layers;l++){
        if(l == 0)
            re = this->tileset.getPassable(this->ids[l+(x+y*this->width)*this->layers]);
        else
            re = re && this->tileset.getPassable(this->ids[l+(x+y*this->width)*this->layers]);
    }

    return re;
}

F2C::uint Tilemap::getWidth() const{
    return this->width;
}
F2C::uint Tilemap::getHeight() const{
    return this->height;
}
F2C::uint Tilemap::getLayers() const{
    return this->layers;
}

void Tilemap::render(){
    if(this->tileset.getTileW() < 1 || this->tileset.getTileH() < 1 || this->width < 1 || this->height < 1)
        return;

    int oox = (this->ox*-1) % (this->tileset.getTileW()*this->width);
    int ooy = (this->oy*-1) % (this->tileset.getTileH()*this->height);
    if(oox < 0)
        oox = this->tileset.getTileW()*this->width + oox;
    if(ooy < 0)
        ooy = this->tileset.getTileH()*this->height + ooy;
    oox = std::min<int>(this->tileset.getTileW()*this->width-this->viewport.clip_rect.width,oox);
    ooy = std::min<int>(this->tileset.getTileH()*this->height-this->viewport.clip_rect.height,ooy);
    oox = std::max<int>(oox,0);
    ooy = std::max<int>(ooy,0);

    if(this->lastviewport.clip_rect.width != this->viewport.clip_rect.width ||
        this->lastviewport.clip_rect.height != this->viewport.clip_rect.height ||
        this->lasttileW != this->tileset.getTileW() || this->lasttileH != this->tileset.getTileH()){
            size_t w = std::min(this->width,this->viewport.clip_rect.width/this->tileset.getTileW()+1);
            size_t h = std::min(this->height,this->viewport.clip_rect.height/this->tileset.getTileH()+1);
            this->spr.elements.resize(w*h*this->layers);
            this->lastviewport = this->viewport;
            this->lasttileW = this->tileset.getTileW();
            this->lasttileH = this->tileset.getTileH();
    }
    size_t mapx =  static_cast<size_t>(oox/this->tileset.getTileW());
    size_t mapy =  static_cast<size_t>(ooy/this->tileset.getTileH());
    size_t mapw =  static_cast<size_t>((this->viewport.clip_rect.width)/this->tileset.getTileW())+1;
    size_t maph =  static_cast<size_t>((this->viewport.clip_rect.height)/this->tileset.getTileH())+1;

    if(this->lastmap.x != mapx || this->lastmap.y != mapy ||
        this->lastmap.width != mapw || this->lastmap.height != maph){
            this->updateSpr(mapx,mapy,mapw,maph);
            this->lastmap.set(mapx,mapy,mapw,maph);
    }
    this->spr.x = this->x;
    this->spr.y = this->y;
    this->spr.z = this->z;
    this->spr.render();
}
