#include "Tilemap.hpp"

Tilemap::Tilemap():
    width(0),
    height(0),
    layers(0),
    x(0),
    y(0),
    z(0),
    ox(0),
    oy(0)
{}

Tilemap::Tilemap(F2C::Viewport viewport,F2C::uint width,F2C::uint height,F2C::uint layers):
    width(width),
    height(height),
    layers(layers),
    x(0),
    y(0),
    z(0),
    ox(0),
    oy(0),
    viewport(viewport)
{
    this->mapTileids.resize(width*height*layers,0);
    this->mapAniids.resize(width*height*layers,0);
}

void Tilemap::loadTileset(const Tileset& tileset){
    this->tileset = tileset;

    this->sprTilemap.setBitmap(&this->tileset.getTileset());

    this->sprAniTiles.clear();
    const std::vector<AniTile>& anitiles = this->tileset.getAniTiles();
    for(size_t i = 0;i < anitiles.size();++i){
        this->sprAniTiles.push_back( ArraySpriteAnimation () );
        this->sprAniTiles.back().setBitmap(&anitiles[i].tile);
        this->sprAniTiles.back().maxframe = anitiles[i].tile.getWidth()/this->tileset.getTileWidth();
        this->sprAniTiles.back().setFrameperWidth(this->sprAniTiles.back().maxframe);
        this->sprAniTiles.back().setFrameperHeight(1);
        this->sprAniTiles.back().endless = true;
        this->sprAniTiles.back().framepertime = true;
    }
}
const Tileset& Tilemap::getTileset() const{
    return this->tileset;
}

void Tilemap::setAniTileid(int x,int y,int layer,size_t id){
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return;

    this->mapAniids[layer+(x+y*this->width)*this->layers] = id+1;
}
void Tilemap::removeAniTileid(int x,int y,int layer){
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return;

    this->mapAniids[layer+(x+y*this->width)*this->layers] = 0;
}

size_t Tilemap::getAniTileid(int x,int y,int layer) const{
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return 0;

    return this->mapAniids[layer+(x+y*this->width)*this->layers]-1;
}

bool Tilemap::isSetAniTileid(int x,int y,int layer) const{
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return false;

    return static_cast<int>(this->mapAniids[layer+(x+y*this->width)*this->layers]) > 0;
}

void Tilemap::setTileid(int x,int y,int layer,size_t id){
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return;

    this->mapTileids[layer+(x+y*this->width)*this->layers] = id;
}
size_t Tilemap::getTileid(int x,int y,int layer) const{
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return 0;

    return this->mapTileids[layer+(x+y*this->width)*this->layers];
}
int Tilemap::getPriority(int x,int y,int layer) const{
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return 0;

    return this->tileset.getPriorities(this->mapTileids[layer+(x+y*this->width)*this->layers]);
}
bool Tilemap::getPassable(int x,int y,int layer) const{
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return true;

    return this->tileset.getPassable(this->mapTileids[layer+(x+y*this->width)*this->layers]);
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

void Tilemap::update(){
    for(size_t i = 0;i < this->sprAniTiles.size();i++){
        this->sprAniTiles[i].update();
    }
}

void Tilemap::setTileArrayRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t startid){
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return;

    size_t endx = std::min(x+width,this->width);
    size_t endy = std::min(y+height,this->height);

    F2C::Rect tsetcoord = this->tileset.getTilesetCoord(startid);
    for(size_t yy = y,ty = tsetcoord.y;
        yy < endy && ty < this->tileset.getTilesPerHeight();yy++,ty++){
            for(size_t xx = x,tx = tsetcoord.x;
            xx < endx && tx < this->tileset.getTilesPerWidth();xx++,tx++){

                size_t id = tx+ty*this->tileset.getTilesPerWidth();
                if(id >= this->tileset.getTilesSize())
                    return;

                this->setTileid(xx,yy,layer,id);
            }
    }
}

void Tilemap::fillTileRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t id){
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return;

    size_t endx = std::min(x+width,this->width);
    size_t endy = std::min(y+height,this->height);

    for(size_t yy = y;yy < endy;yy++){
        for(size_t xx = x;xx < endx;xx++){
            this->setTileid(xx,yy,layer,id);
        }
    }
}

void Tilemap::fillTileLayer(int layer,size_t id){
    this->fillTileRect(0,0,layer,this->width,this->height,id);
}

void Tilemap::fillAniTileRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t id){
    if(x < 0 || y < 0 || layer < 0 || x > this->width || y > this->height || layer > this->layers)
        return;

    size_t endx = std::min(x+width,x+this->width);
    size_t endy = std::min(y+height,y+this->height);

    for(size_t yy = y;yy < endy;yy++){
        for(size_t xx = x;xx < endx;xx++){
            this->setAniTileid(xx,yy,layer,id);
        }
    }
}

void Tilemap::fillAniTileLayer(int layer,size_t id){
    this->fillAniTileRect(0,0,layer,this->width,this->height,id);
}

void Tilemap::render(){
    this->sprTilemap.setViewport(&this->viewport);

    int startx = this->ox/this->tileset.getTileWidth();
    int starty = this->oy/this->tileset.getTileHeight();
    startx = std::max(startx,0);
    starty = std::max(starty,0);

    for(size_t layer = 0;layer < this->layers;layer++){
        int rendery = 0;
        for(size_t y = starty;y < this->height && rendery < this->viewport.clip_rect.height;y++){
            this->sprTilemap.elements.clear();
            for(size_t i = 0;i < this->sprAniTiles.size();i++)
                this->sprAniTiles[i].elements.clear();

            int renderx = 0;
            for(size_t x = startx;x < this->width && renderx < this->viewport.clip_rect.width;x++){
                size_t tileid = this->mapTileids[layer+(x+y*this->width)*this->layers];
                size_t anitileid = this->mapAniids[layer+(x+y*this->width)*this->layers];

                if(anitileid > 0 && anitileid-1 < this->sprAniTiles.size()){
                    this->sprAniTiles[anitileid-1].elements.push_back(F2C::SpriteElement());
                    this->sprAniTiles[anitileid-1].elements.back().x = this->x + renderx;
                    this->sprAniTiles[anitileid-1].elements.back().y = this->y + rendery;
                    this->sprAniTiles[anitileid-1].elements.back().z = this->z + this->tileset.getPriorities(tileid,true)*32;
                    if(x == startx){
                        this->sprAniTiles[anitileid-1].elements.back().x -= this->ox % this->tileset.getTileWidth();
                    }
                    if(y == starty){
                        this->sprAniTiles[anitileid-1].elements.back().y -= this->oy % this->tileset.getTileHeight();
                    }
                }else if(tileid < this->tileset.getTilesSize()){
                    this->sprTilemap.elements.push_back(F2C::SpriteElement());
                    this->sprTilemap.elements.back().x = this->x + renderx;
                    this->sprTilemap.elements.back().y = this->y + rendery;
                    this->sprTilemap.elements.back().z = this->z + this->tileset.getPriorities(tileid)*32;
                    this->sprTilemap.elements.back().src_rect = this->tileset.getTileCoord(tileid);
                    if(x == startx){
                        this->sprTilemap.elements.back().x -= this->ox % this->tileset.getTileWidth();
                    }
                    if(y == starty){
                        this->sprTilemap.elements.back().y -= this->oy % this->tileset.getTileHeight();
                    }
                }

                if(x == startx)
                    renderx += this->tileset.getTileWidth() - (this->ox % this->tileset.getTileWidth());
                else
                    renderx += this->tileset.getTileWidth();
            }

            this->sprTilemap.render();
            for(size_t i = 0;i < this->sprAniTiles.size();i++){
                this->sprAniTiles[i].refreshSrcRect();
                this->sprAniTiles[i].render();
            }

            if(y == starty)
                rendery += this->tileset.getTileHeight() - (this->oy % this->tileset.getTileHeight());
            else
                rendery += this->tileset.getTileHeight();
        }
    }
}
