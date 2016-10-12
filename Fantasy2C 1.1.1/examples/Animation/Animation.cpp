#include "Animation.hpp"

Timer::Timer():
    starttime(0.0f)
{
    F2C::Window app;
    this->starttime = app.getTime();
}

void Timer::reset(){
    F2C::Window app;
    this->starttime = app.getTime();
}

double Timer::getTime(){
    F2C::Window app;
    return app.getTime()-this->starttime;
}

Animation::Animation():
    frameWidth(0),
    frameHeight(0),
    frame(0),
    end(false),
    maxframeWidth(1),
    maxframeHeight(1),
    maxframe(1),
    framepertime(false),
    endless(true),
    pause(false),
    secperframe(0.2f)
{}

void Animation::reset(){
    this->frame = 0;
    this->frameWidth = 0;
    this->frameHeight = 0;
    this->end = false;
}

bool Animation::getEnd() const{
    return this->end;
}

void Animation::stop(){
    this->pause = true;
    this->reset();
}

void Animation::setFrameperWidth(F2C::uint width){
    if(width > 0)
        this->maxframeWidth = std::min<F2C::uint>(1,this->getSprWidth()/width);
    else
        this->maxframeWidth = 1;

    this->maxframe = this->maxframeWidth*this->maxframeHeight;
}

void Animation::setFrameperHeight(F2C::uint height){
    if(height > 0)
        this->maxframeHeight = std::min<F2C::uint>(1,this->getSprHeight()/height);
    else
        this->maxframeHeight = 1;

    this->maxframe = this->maxframeWidth*this->maxframeHeight;
}

F2C::uint Animation::getFrameWidth() const{
    if(this->maxframeWidth < 2)
        return this->getSprWidth();
    else
        return this->getSprWidth()/this->maxframeWidth;

}

F2C::uint Animation::getFrameHeight() const{
    if(this->maxframeHeight < 2)
        return this->getSprHeight();
    else
        return this->getSprHeight()/this->maxframeHeight;

}

void Animation::nextFrame(){
    if((this->frameWidth+1 >= this->maxframeWidth && this->frameHeight+1 >= this->maxframeHeight) ||
        this->frame+1 >= this->maxframe)
        this->end = true;
    else{
        if(this->frameWidth+1 >= this->maxframeWidth){
            this->frameHeight = (this->frameHeight+1) % this->maxframeHeight;
            this->frameWidth = 0;
        }else
            this->frameWidth = (this->frameWidth+1) % this->maxframeWidth;
        this->frame++;
    }
}

void Animation::update(){
    if(this->maxframeWidth < 2 && this->maxframeHeight < 2 )
        return;

    if(!this->pause){
        if(this->timer.getTime() == 0.0f)
            this->timer.reset();

        if(this->endless){
            if(this->framepertime && this->secperframe != 0.0f){
                if(this->timer.getTime() >= this->secperframe){
                    this->timer.reset();
                    this->nextFrame();
                }
            }else{
                this->nextFrame();
            }
            if(this->end)
                this->reset();
        }else if(!this->end){
            if(this->framepertime){
                if(this->timer.getTime() >= this->secperframe){
                    this->nextFrame();
                    this->timer.reset();
                }
            }else{
                this->nextFrame();
            }
        }
    }

    if(this->maxframeWidth > 1){
        this->ani_src_rect.x = this->frameWidth*(this->getSprWidth()/this->maxframeWidth);
        this->ani_src_rect.width = this->getSprWidth()/this->maxframeWidth;
    }else{
        this->ani_src_rect.x = 0;
        this->ani_src_rect.width = 0;
    }
    if(this->maxframeHeight > 1){
        this->ani_src_rect.y = this->frameHeight*(this->getSprHeight()/this->maxframeHeight);
        this->ani_src_rect.height = this->getSprHeight()/this->maxframeHeight;
    }else{
        this->ani_src_rect.y = 0;
        this->ani_src_rect.height = 0;
    }
}

F2C::uint SimpleSpriteAnimation::getSprWidth() const{
    return this->getTexWidth();
}
F2C::uint SimpleSpriteAnimation::getSprHeight() const{
    return this->getTexHeight();
}

void SimpleSpriteAnimation::update(){
    this->Animation::update();
    this->src_rect = this->ani_src_rect;
}

void SimpleSpriteAnimation::refreshSrcRect(){
    this->src_rect = this->ani_src_rect;
}
