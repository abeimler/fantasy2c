#ifndef TILESET_HPP_INCLUDED
#define TILESET_HPP_INCLUDED

#include <Fantasy2C/Bitmap.hpp>

class Tileset{
    private:
    F2C::Bitmap tileset;
    std::vector<bool> passable;
    std::vector<F2C::Rect> tilecoord;
    std::vector<int> priorities;
    F2C::uint tileW, tileH;
    F2C::uint vtileW;
    F2C::uint vtileH;

    public:
    Tileset();

    void setBitmap(const F2C::Bitmap& bitmap, F2C::uint tileW, F2C::uint tileH);
    F2C::uint getTileW() const;
    F2C::uint getTileH() const;
    size_t getSize() const;
    void setPassable(F2C::uint id, bool value);
    bool getPassable(F2C::uint id) const;
    void setPriorities(F2C::uint id, int value);
    int getPriorities(F2C::uint id) const;
    size_t getID(F2C::uint x,F2C::uint y) const;
    F2C::Rect getTileCoord(F2C::uint id) const;
    const F2C::Bitmap& getBitmap() const;
};

#endif // TILESET_HPP_INCLUDED
