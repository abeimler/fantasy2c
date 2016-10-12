#ifndef TILEMAP_HPP_INCLUDED
#define TILEMAP_HPP_INCLUDED

#include <Fantasy2C/ArraySprite.hpp>
#include "Tileset.hpp"


class Tilemap{
    private:
    Tileset tileset;
    F2C::ArraySprite spr;
    std::vector<size_t> ids;
    F2C::uint width,height,layers;
    F2C::Viewport lastviewport;
    F2C::uint lasttileW,lasttileH;
    F2C::Rect lastmap;

    /**
    *@param x Map x-Coord.
    *@param y Map y-Coord.
    *@param width Map width
    *@param height Map height
    *@brief viewport of map (set sprites)
    */
    void updateSpr(F2C::uint x,F2C::uint y,F2C::uint width,F2C::uint height);

    public:
    int x,y,z; //show Coord.
    int ox,oy; //Map view-Coord.
    F2C::Viewport viewport; //Map viewport

    Tilemap();
    Tilemap(F2C::uint width, F2C::uint height,F2C::uint layers);

    void setTileset(const Tileset& tileset);
    const Tileset& getTileset() const;
    void setID(F2C::uint x,F2C::uint y,F2C::uint layer,F2C::uint id);
    void resize(F2C::uint width, F2C::uint height,F2C::uint layers);
    F2C::uint getID(F2C::uint x,F2C::uint y,F2C::uint layer) const;
    bool getPassable(F2C::uint x,F2C::uint y,F2C::uint layer) const;
    bool getPassable(F2C::uint x,F2C::uint y) const;
    F2C::uint getWidth() const;
    F2C::uint getHeight() const;
    F2C::uint getLayers() const;

    void render();
};

#endif // TILEMAP_HPP_INCLUDED
