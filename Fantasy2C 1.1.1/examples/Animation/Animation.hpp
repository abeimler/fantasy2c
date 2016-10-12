#ifndef ANIMATON_HPP_INCLUDED
#define ANIMATON_HPP_INCLUDED

#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/SimpleSprite.hpp>

class Timer{
    private:
    double starttime;

    public:
    Timer();
    void reset(); //restart/reset Timer
    double getTime(); //in Sec
};

class Animation{
    private:
    Timer timer; ///< timer for Frame per Time
    F2C::uint frameWidth; ///< current frame per Width
    F2C::uint frameHeight; ///< current frame per Height
    F2C::uint frame;   ///< current frame
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
    F2C::uint maxframeWidth; ///< maximal frames per Width
    F2C::uint maxframeHeight; ///< maximal frames per Height
    F2C::uint maxframe; ///< absolute maximal frames
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

    /**
    *@param height height of an frame
    *@brief set maxframe per height (getSprHeight()/height)
    */
    void setFrameperHeight(F2C::uint height);

    bool getEnd() const; ///< @return get end
    void stop(); ///< stop animation

    void reset(); ///< reset animation
    void update(); ///< update frame
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
};

#endif // ANIMATON_HPP_INCLUDED
