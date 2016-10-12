#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include "basic.h"
namespace F2C{

class Tilemap{
    private:
    F2C::SimpleSprite tile_spr;
    F2C::uint width,height,layers;
    std::vector< std::vector< std::vector<F2C::uint> > > map_ids;
    std::vector< std::vector< std::vector<int> > > priorities;
    std::vector<F2C::Rect> rect_id;

    public:
    static F2C::uint tilewidth;
    static F2C::uint tileheight;

    Tilemap();
    Tilemap(F2C::uint width,F2C::uint height,F2C::uint layers = 3);

    F2C::Viewport viewport;
    int x,y;
    int ox,oy;
    bool show;
    int active_layer;

    bool SaveMap(std::string filename);
    bool LoadMap(std::string filename);
    void setBitmap(F2C::Bitmap* bitmap);
    void ReSize(F2C::uint width,F2C::uint height);
    void ReSize(F2C::uint width,F2C::uint height,F2C::uint layers);
    void render();

    void setAllMapIDs(F2C::uint id);
    void setAllMapIDs(F2C::uint id, F2C::uint layers);

    uint getMapID(F2C::uint x, F2C::uint y, F2C::uint layer) const;
    void setMapID(F2C::uint x, F2C::uint y, F2C::uint layer, F2C::uint id);

    uint getPriority(F2C::uint x,F2C::uint y,F2C::uint layer) const;
    void setPriority(F2C::uint x,F2C::uint y,F2C::uint layer,F2C::uint pro);
    const std::vector<F2C::Rect>& getRectIDs() const;
    uint getWidth() const;
    uint getHeight() const;
    uint getLayers() const;
    F2C::SimpleSprite* getSprite();
    const F2C::SimpleSprite* getSprite() const;
};

};
#endif // TILEMAP_H_INCLUDED
