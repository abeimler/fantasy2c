#ifndef ANIMATON_HPP_INCLUDED
#define ANIMATON_HPP_INCLUDED

#include "basic.h"

class Animation{
    private:
    F2C::Timer timer; ///< timer for Frame per Time
    F2C::uint frame; ///< current frame
    bool end; ///< is last Frame, end of Animation

    void nextFrame(); ///< goto next Frame

    protected:
    /**
    *@return width of Sprite @brief width of Sprite , e.g. return Sprite.getTexWidth()
    */
    virtual F2C::uint getSprWidth() const = 0;

    /**
    *@return height of Sprite @brief height of Sprite , e.g. return Sprite.getTexHeight()
    */
    virtual F2C::uint getSprHeight() const = 0;

    F2C::Rect ani_src_rect; ///< current frame position

    public:
    F2C::uint maxframe; ///< maximal frames
    bool framepertime; ///< use Timer
    bool endless; ///< is endless Animation
    bool pause; ///< Animation pause
    double secperframe; ///< 1 frame in ... sec

    Animation();

    /**
    *@param width width of an frame
    *@brief set maxframe per width (getSprWidth()/width)
    */
    void setFrameperWidth(F2C::uint width);

    bool getEnd() const; ///< @return get end
    void stop(); ///< stop animation

    void reset(); ///< reset animation
    void update(); ///< update frame
    F2C::uint getFrameWidth() const; ///< get width of an frame
};

class SimpleSpriteAnimation : public Animation , public F2C::SimpleSprite{
    private:
    F2C::uint getSprWidth() const;
    F2C::uint getSprHeight() const;

    public:
    SimpleSpriteAnimation(){}

    void update();
    void refreshSrcRect();
};

class ArraySpriteAnimation : public Animation , public F2C::ArraySprite{
    private:
    F2C::uint getSprWidth() const;
    F2C::uint getSprHeight() const;

    public:
    ArraySpriteAnimation(){}
    ArraySpriteAnimation(const F2C::Bitmap* bitmap);

    void update();
    void refreshSrcRect();
};

#endif // ANIMATON_HPP_INCLUDED
