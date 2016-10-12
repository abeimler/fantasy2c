#ifndef TILESET_HPP_INCLUDED
#define TILESET_HPP_INCLUDED

#include "Animation.hpp"

class Tile{
    public:
    F2C::Rect coord;
    int priority;
    bool passable;

    Tile();
};

class AniTile{
    public:
    F2C::Bitmap tile;
    int priority;
    bool passable;

    AniTile();
};

class Tileset{
    private:
    F2C::Bitmap tileset;
    std::vector<Tile> tiles;
    F2C::uint tileWidth;
    F2C::uint tileHeight;

    void refreshCoordTiles();

    public:
    std::vector<AniTile> anitiles;

    static F2C::uint defaultTileWidth;
    static F2C::uint defaultTileHeight;

    Tileset(F2C::uint tileWidth = Tileset::defaultTileWidth,F2C::uint tileHeight = Tileset::defaultTileHeight);

    void loadTileset(std::string filename,F2C::uint tileWidth = Tileset::defaultTileWidth,F2C::uint tileHeight = Tileset::defaultTileHeight);
    void loadTileset(const F2C::Bitmap& bitmap,F2C::uint tileWidth = Tileset::defaultTileWidth,F2C::uint tileHeight = Tileset::defaultTileHeight);

    void addAniTile(std::string filename);
    void addAniTile(const F2C::Bitmap& bitmap);

    const std::vector<Tile>& getTiles() const;
    const F2C::Bitmap& getTileset() const;
    size_t getTilesSize() const;

    F2C::uint getTileWidth() const;
    F2C::uint getTileHeight() const;

    F2C::uint getTilesPerWidth() const;
    F2C::uint getTilesPerHeight() const;

    size_t getTileID(int x,int y) const;
    F2C::Rect getTileCoord(size_t id) const;
    int getPriorities(size_t id,bool isAniTile = false) const;
    bool getPassable(size_t id,bool isAniTile = false) const;
    F2C::Rect getTilesetCoord(size_t id) const;

    void setPriorities(size_t id,int priority,bool isAniTile = false);
    void setPassable(size_t id,bool passable,bool isAniTile = false);
};

#endif // TILESET_HPP_INCLUDED
