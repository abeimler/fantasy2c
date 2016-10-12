#include "Animation.hpp"

Animation::Animation():
    frame(0),
    frameWidth(0),
    frameHeight(0),
    maxframeWidth(1),
    maxframeHeight(1),
    end(false),
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

bool Animation::isEnd() const{
    return this->end;
}

void Animation::stop(){
    this->pause = true;
    this->reset();
}

void Animation::setFrameperWidth(F2C::uint frames){
    if(frames > 0)
        this->maxframeWidth = frames;
    else
        this->maxframeWidth = 1;
}

F2C::uint Animation::getFrameWidth() const{
    if(this->maxframeWidth <= 1)
        return this->getSprWidth();
    else
        return this->getSprWidth()/this->maxframeWidth;

}

void Animation::setFrameperHeight(F2C::uint frames){
    if(frames > 0)
        this->maxframeHeight = frames;
    else
        this->maxframeHeight = 1;
}

F2C::uint Animation::getFrameHeight() const{
    if(this->maxframeHeight <= 1)
        return this->getSprHeight();
    else
        return this->getSprHeight()/this->maxframeHeight;

}

void Animation::nextFrame(){
    if(this->frame >= this->maxframe)
        this->frame = 0;

    this->frameWidth++;
    if(this->frameWidth >= this->maxframeWidth){
        this->frameWidth = 0;
        this->frameHeight++;
    }
    if(this->frameHeight >= this->maxframeHeight){
        this->frameHeight = 0;
    }
    this->frame++;
    this->end = this->frame >= this->maxframe;
}

void Animation::update(){
    if(this->maxframeWidth <= 1 && this->maxframeHeight <= 1)
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

    this->refreshFrame();
}

void Animation::refreshFrame(){
    this->ani_src_rect.set( this->frameWidth*getFrameWidth(),
                            this->frameHeight*getFrameHeight(),
                            getFrameWidth(),
                            getFrameHeight());
}

F2C::uint SimpleSpriteAnimation::getSprWidth() const{
    return this->getTexWidth();
}
F2C::uint SimpleSpriteAnimation::getSprHeight() const{
    return this->getTexHeight();
}

void SimpleSpriteAnimation::update(){
    this->Animation::update();
    this->refreshSrcRect();
}

void SimpleSpriteAnimation::refreshSrcRect(){
    this->refreshFrame();
    this->src_rect = this->ani_src_rect;
}

F2C::uint ArraySpriteAnimation::getSprWidth() const{
    return this->getTexWidth();
}
F2C::uint ArraySpriteAnimation::getSprHeight() const{
    return this->getTexHeight();
}

void ArraySpriteAnimation::update(){
    this->Animation::update();
    this->refreshSrcRect();
}

void ArraySpriteAnimation::refreshSrcRect(){
    this->refreshFrame();
    for(size_t i = 0;i < this->elements.size();i++)
        this->elements[i].src_rect = this->ani_src_rect;
}
