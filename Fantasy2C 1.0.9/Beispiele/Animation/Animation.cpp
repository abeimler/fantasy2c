#include "Animation.hpp"

Timer::Timer():
    starttime(F2C::Window::getInstance()->getTime())
{}

void Timer::reset(){
    this->starttime = F2C::Window::getInstance()->getTime();
}

double Timer::getTime(){
    return F2C::Window::getInstance()->getTime()-this->starttime;
}

Animation::Animation():
    frame(0),
    framex(0),
    framey(0),
    end(false),
    maxframe(1),
    frameperwidth(1),
    frameperheight(1),
    framepertime(false),
    endless(false),
    pause(false),
    secperframe(0.05f)
{}

void Animation::reset(){
    this->framex = 0;
    this->framey = 0;
    this->frame = 0;
    this->end = false;
    this->pause = false;
}

bool Animation::getEnd(){
    return this->end;
}

void Animation::stop(){
    this->end = true;
    this->framex = 0;
    this->framey = 0;
    this->frame = 0;
    this->endless = false;
    this->pause = true;
}

F2C::uint Animation::getFrameWidth() const{
    if(this->frameperwidth <= 1)
        return this->getTexWidth();
    else
        return this->getTexWidth()/this->frameperwidth;
}

F2C::uint Animation::getFrameHeight() const{
    if(this->frameperheight <= 1)
        return this->getTexHeight();
    else
        return this->getTexHeight()/this->frameperheight;

}

void Animation::gotoNextFrame(){
    if(this->end)
        return;

    this->framex++; //goto next column
    if(this->framex >= this->frameperwidth){
        //goto next line
        this->framex = 0;
        this->framey++;
    }
    if(this->framey >= this->frameperheight){
        //stop, end of animation
        this->framey = this->frameperheight;
        this->end = true;
    }
    if(!this->end)
        this->frame++; //next frame
    if(this->frame >= this->maxframe-1){
        //stop, end of animation
        this->frame = this->maxframe-1;
        this->end = true;
    }
}

void Animation::update(){
    if(this->maxframe <= 1 || this->frameperwidth <= 1 || this->frameperheight <= 1){
        this->src_rect.set(0,0,0,0);
        return;
    }
    if(this->timer.getTime() == 0.0f)
        this->timer.reset();

    if(!this->pause){
        //endless
        if(this->endless){
            if(this->end){
                this->reset();
            }

            //use timer
            if(this->framepertime && this->timer.getTime() >= this->secperframe){
                this->gotoNextFrame();
                this->timer.reset();

            //use FPS
            }else if(!this->framepertime){
                this->gotoNextFrame();
            }

        //unique animation
        }else if(!this->end){
            //use timer
            if(this->framepertime && this->timer.getTime() >= this->secperframe){
                this->gotoNextFrame();
                this->timer.reset();

            //use FPS
            }else if(!this->framepertime){
                this->gotoNextFrame();
            }
        }
    }

    F2C::uint fw = this->getFrameWidth();
    F2C::uint fh = this->getFrameHeight();
    this->src_rect.set(this->framex*fw,this->framey*fh,fw,fh);
}
