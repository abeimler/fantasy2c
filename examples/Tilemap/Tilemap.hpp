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

    ///create Tilemap with the Viewport,width/height of Tilemap and numbers of layers
    Tilemap(F2C::Viewport viewport,F2C::uint width,F2C::uint height,F2C::uint layers = 1);

    void loadTileset(const Tileset& tileset); ///< load Tileset
    const Tileset& getTileset() const; ///< get Tileset

    ///set Tiles(of Tilset)
    void setTileid(int x,int y,int layer,size_t id);
    void setAniTileid(int x,int y,int layer,size_t id);
    void removeAniTileid(int x,int y,int layer);

    /**
    *@param x X-Coord to set in Map
    *@param y Y-Coord to set in Map
    *@param width width(numbers of Tile) of Tile-Block
    *@param height height(numbers of Tile) of Tile-Block
    *@brief set an Tile-Block
    */
    void setTileArrayRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t startid);

    ///fill a Rect(in the Tilemap) with Tiles
    void fillTileRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t id);
    void fillTileLayer(int layer,size_t id); ///< fill a Tilemap-Layer with Tiles

    ///fill a Rect(in the Tilemap) with AniTiles
    void fillAniTileRect(int x,int y,int layer,F2C::uint width,F2C::uint height,size_t id);
    void fillAniTileLayer(int layer,size_t id); ///< fill a Tilemap-Layer with AniTiles

    ///get (Ani)TileID, priority, passable or is set an AniTileid
    size_t getAniTileid(int x,int y,int layer) const;
    size_t getTileid(int x,int y,int layer) const;
    int getPriority(int x,int y,int layer) const;
    bool getPassable(int x,int y,int layer) const;
    bool isSetAniTileid(int x,int y,int layer) const;

    ///site of Tilemap
    F2C::uint getWidth() const;
    F2C::uint getHeight() const;
    F2C::uint getLayers() const;

    void update(); ///< update AniTiles
    void render(); ///< render Tilemap (in the Viewport-Area)
};

#endif // TILEMAP_HPP_INCLUDED
