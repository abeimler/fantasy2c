#include "Tileset.hpp"


Tile::Tile():
    priority(0),
    passable(true)
{}

AniTile::AniTile():
    priority(0),
    passable(true)
{}

F2C::uint Tileset::defaultTileWidth = 32;
F2C::uint Tileset::defaultTileHeight = 32;

Tileset::Tileset(F2C::uint tileWidth,F2C::uint tileHeight):
    tileWidth(tileWidth),
    tileHeight(tileHeight)
{}

void Tileset::refreshCoordTiles(){
    this->tiles.clear();
    for(size_t y = 0;y < this->tileset.getHeight();y+=this->tileHeight){
        for(size_t x = 0;x < this->tileset.getWidth();x+=this->tileWidth){
            this->tiles.push_back(Tile());
            this->tiles.back().coord.set(x,y,this->tileWidth,this->tileHeight);
        }
    }
}

void Tileset::loadTileset(std::string filename,F2C::uint tileWidth,F2C::uint tileHeight){
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    F2CLoadBitmap(this->tileset,filename);

    this->refreshCoordTiles();
}
void Tileset::loadTileset(const F2C::Bitmap& bitmap,F2C::uint tileWidth,F2C::uint tileHeight){
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    this->tileset = bitmap;

    this->refreshCoordTiles();
}

void Tileset::addAniTile(std::string filename){
    this->anitiles.push_back(AniTile());
    F2CLoadBitmap(this->anitiles.back().tile,filename);
}
void Tileset::addAniTile(const F2C::Bitmap& bitmap){
    this->anitiles.push_back(AniTile());
    this->anitiles.back().tile = bitmap;
}

void Tileset::removeAniTile(size_t id){
    if(id >= this->anitiles.size())
        return;

    this->anitiles.erase(this->anitiles.begin()+id);
}

const std::vector<Tile>& Tileset::getTiles() const{
    return this->tiles;
}
const std::vector<AniTile>& Tileset::getAniTiles() const{
    return this->anitiles;
}
size_t Tileset::getTilesSize() const{
    return this->tiles.size();
}
const F2C::Bitmap& Tileset::getTileset() const{
    return this->tileset;
}

F2C::uint Tileset::getTileWidth() const{
    return this->tileWidth;
}
F2C::uint Tileset::getTileHeight() const{
    return this->tileHeight;
}

F2C::uint Tileset::getTilesPerWidth() const{
    return this->tileset.getWidth()/this->tileWidth;
}
F2C::uint Tileset::getTilesPerHeight() const{
    return this->tileset.getHeight()/this->tileHeight;
}

size_t Tileset::getTileID(int x,int y) const{
    F2C::Rect xyCoord (x,y,1,1);
    for(size_t i = 0;i < this->tiles.size();i++){
        if(this->tiles[i].coord.collision(xyCoord) )
            return i;
    }
    return 0;
}

F2C::Rect Tileset::getTileCoord(size_t id) const{
    if(id >= this->tiles.size())
        return F2C::Rect (0,0,0,0);
    else
        return this->tiles[id].coord;
}

F2C::Rect Tileset::getTilesetCoord(size_t id) const{
    if(id >= this->tiles.size())
        return F2C::Rect (0,0,0,0);
    else{
        F2C::Rect re;
        re.x = this->tiles[id].coord.x/this->tileWidth;
        re.y = this->tiles[id].coord.y/this->tileHeight;
        return re;
    }
}

int Tileset::getPriorities(size_t id,bool isAniTile) const{
    if(isAniTile){
        if(id >= this->anitiles.size())
            return 0;
        else
            return this->anitiles[id].priority;
    }else{
        if(id >= this->tiles.size())
            return 0;
        else
            return this->tiles[id].priority;
    }
}
bool Tileset::getPassable(size_t id,bool isAniTile) const{
    if(isAniTile){
        if(id >= this->anitiles.size())
            return true;
        else
            return this->anitiles[id].passable;
    }else{
        if(id >= this->tiles.size())
            return true;
        else
            return this->tiles[id].passable;
    }
}

void Tileset::setPriorities(size_t id,int priority,bool isAniTile){
    if(isAniTile){
        if(id >= this->anitiles.size())
            return;
        else
            this->anitiles[id].priority = priority;
    }else{
        if(id >= this->tiles.size())
            return;
        else
            this->tiles[id].priority = priority;
    }
}
void Tileset::setPassable(size_t id,bool passable,bool isAniTile){
    if(isAniTile){
        if(id >= this->anitiles.size())
            return;
        else
            this->anitiles[id].passable = passable;
    }else{
        if(id >= this->tiles.size())
            return;
        else
            this->tiles[id].passable = passable;
    }
}
