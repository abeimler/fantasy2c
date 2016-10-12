#ifndef TILEMAP_HPP_INCLUDED
#define TILEMAP_HPP_INCLUDED

#include "Tileset.hpp"

class Tilemap{
    private:
    Tileset tileset;
    std::vector<size_t> mapTileids; //tileset ids
    std::vector<size_t> mapAniids; //anitile ids

    std::vector<ArraySpriteAnimation> sprAniTiles;
    F2C::ArraySprite sprTilemap;

    F2C::uint width;
    F2C::uint height;
    F2C::uint layers;

    public:
    int x;
    int y;
    int z;
    int ox;
    int oy;
    F2C::Viewport viewport;

    Tilemap();
    Tilemap(F2C::Viewport viewport,F2C::uint width,F2C::uint height,F2C::uint layers = 1);

    void loadTileset(const Tileset& tileset);
    const Tileset& getTileset() const;

    void setTileid(int x,int y,int layer,size_t id);
    void setAniTileid(int x,int y,int layer,size_t id);
    void deleteAniTileid(int x,int y,int layer);

    void setTileArrayRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t startid);
    void fillTileRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t id);
    void fillTileLayer(int layer,size_t id);
    void fillAniTileRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t id);
    void fillAniTileLayer(int layer,size_t id);

    size_t getAniTileid(int x,int y,int layer) const;
    size_t getTileid(int x,int y,int layer) const;
    int getPriority(int x,int y,int layer) const;
    bool getPassable(int x,int y,int layer) const;
    bool isSetAniTileid(int x,int y,int layer) const;

    F2C::uint getWidth() const;
    F2C::uint getHeight() const;
    F2C::uint getLayers() const;

    void update();
    void render();
};

#endif // TILEMAP_HPP_INCLUDED
