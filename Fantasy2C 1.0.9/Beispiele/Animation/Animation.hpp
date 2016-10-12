#ifndef __ANIMATON_HPP_INCLUDED
#define __ANIMATON_HPP_INCLUDED

#include <Fantasy2C/SimpleSprite.hpp>
#include <Fantasy2C/Window.hpp>

class Timer{
    private:
    double starttime;

    public:
    Timer();
    void reset(); //restart/reset Timer
    double getTime(); //in Sec
};

class Animation : public F2C::SimpleSprite{
    private:
    Timer timer;
    F2C::uint frame;
    F2C::uint framex;
    F2C::uint framey;
    bool end;

    void gotoNextFrame();

    public:
    F2C::uint maxframe; //numbers of frames in animation
    F2C::uint frameperwidth; //numb4ers of frames per width
    F2C::uint frameperheight; //numb4ers of frames per height
    bool framepertime; //use FPS or timer (goto next frame)
    bool endless; //endles animation
    bool pause; //pause
    double secperframe; //goto next frame in sec

    Animation();

    bool getEnd(); //is end of animation (last frame)
    void stop(); //stop animation (end = true)

    void reset(); //stop animation (end = false)
    void update(); //update animation
    F2C::uint getFrameWidth() const; //width of 1 frame
    F2C::uint getFrameHeight() const; //height of 1 frame
};

#endif // ANIMATON_HPP_INCLUDED
