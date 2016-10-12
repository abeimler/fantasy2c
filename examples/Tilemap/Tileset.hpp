#ifndef TILESET_HPP_INCLUDED
#define TILESET_HPP_INCLUDED

#include "basic.h"
#include "Animation.hpp"

class Tile{
    public:
    F2C::Rect coord; ///< coord/size  of Tile
    int priority; ///< z-cooud = 32*priority
    bool passable; ///< is tile passable

    Tile();
};

class AniTile{
    public:
    F2C::Bitmap tile; ///< animation bitmap
    int priority; ///< z-cooud = 32*priority
    bool passable; ///< is tile passable

    AniTile();
};

class Tileset{
    private:
    F2C::Bitmap tileset;
    std::vector<Tile> tiles;
    std::vector<AniTile> anitiles;
    F2C::uint tileWidth;
    F2C::uint tileHeight;

    void refreshCoordTiles();

    public:
    static F2C::uint defaultTileWidth;
    static F2C::uint defaultTileHeight;

    ///set width/height of Tiles
    Tileset(F2C::uint tileWidth = Tileset::defaultTileWidth,F2C::uint tileHeight = Tileset::defaultTileHeight);

    void loadTileset(std::string filename,F2C::uint tileWidth = Tileset::defaultTileWidth,F2C::uint tileHeight = Tileset::defaultTileHeight);
    void loadTileset(const F2C::Bitmap& bitmap,F2C::uint tileWidth = Tileset::defaultTileWidth,F2C::uint tileHeight = Tileset::defaultTileHeight);

    ///load and add an AniTile
    void addAniTile(std::string filename);
    void addAniTile(const F2C::Bitmap& bitmap);
    void removeAniTile(size_t id); ///< remove AniTile

    const std::vector<Tile>& getTiles() const; ///< get tiles
    const std::vector<AniTile>& getAniTiles() const; ///< get AniTiles
    const F2C::Bitmap& getTileset() const; ///< get tileset-bitmap (not AniTiles)
    size_t getTilesSize() const; ///< get Numbers of Tiles

    ///size of 1 Tile
    F2C::uint getTileWidth() const;
    F2C::uint getTileHeight() const;

    ///tiles per Width/Height of the tileset-bitmap
    F2C::uint getTilesPerWidth() const;
    F2C::uint getTilesPerHeight() const;

    size_t getTileID(int x,int y) const; ///< get tileset ID
    F2C::Rect getTileCoord(size_t id) const; ///< get Tileset Coord
    int getPriorities(size_t id,bool isAniTile = false) const; ///< get priority of Tile(or AniTile)
    bool getPassable(size_t id,bool isAniTile = false) const; ///< get passable of Tile(or AniTile)
    F2C::Rect getTilesetCoord(size_t id) const; ///< get Coord. of Tile in the Tileset-bitmap

    void setPriorities(size_t id,int priority,bool isAniTile = false); ///< set priority of Tile(or AniTile)
    void setPassable(size_t id,bool passable,bool isAniTile = false); ///< set passable of Tile(or AniTile)
};

#endif // TILESET_HPP_INCLUDED
