#ifndef ANIMATON_HPP_INCLUDED
#define ANIMATON_HPP_INCLUDED

#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/SimpleSprite.hpp>
#include <Fantasy2C/Sprite.hpp>

class Animation{
    private:
    F2C::Timer timer;
    F2C::uint frame; ///< current frame
    F2C::uint frameWidth; ///< current frame in width
    F2C::uint frameHeight; ///< current frame in height
    F2C::uint maxframeWidth; ///< maxmimal frame in width
    F2C::uint maxframeHeight; ///< maximal frame in height
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
    *@param frames frames per width
    *@brief set maxframe per width
    */
    void setFrameperWidth(F2C::uint frames);

    /**
    *@param frames frames per height
    *@brief set maxframe per height
    */
    void setFrameperHeight(F2C::uint frames);

    bool isEnd() const; ///< @return is last Frame (end of animation)
    void stop(); ///< stop animation

    void reset(); ///< reset animation
    void update(); ///< update frame
    void refreshFrame(); ///< refresh ani_src_rect
    F2C::uint getFrameWidth() const; ///< get width of an frame
    F2C::uint getFrameHeight() const; ///< get height of an frame
};

class SimpleSpriteAnimation : public Animation , public F2C::SimpleSprite{
    private:
    F2C::uint getSprWidth() const;
    F2C::uint getSprHeight() const;

    public:
    SimpleSpriteAnimation(){}

    void update();
    void refreshSrcRect();
    F2C::int16 render(); ///< refresh src_rect and render
};

class SpriteAnimation : public Animation , public F2C::Sprite{
    private:
    F2C::uint getSprWidth() const;
    F2C::uint getSprHeight() const;

    public:
    SpriteAnimation(){}

    void update();
    void refreshSrcRect();
    F2C::int16 render(); ///< refresh src_rect and render
};

#endif // ANIMATON_HPP_INCLUDED
