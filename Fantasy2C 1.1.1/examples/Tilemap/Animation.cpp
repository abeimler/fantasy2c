#include "Animation.hpp"

Animation::Animation():
    frame(0),
    end(false),
    maxframe(1),
    framepertime(false),
    endless(true),
    pause(false),
    secperframe(0.2f)
{}

void Animation::reset(){
    this->frame = 0;
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
        this->maxframe = this->getSprWidth()/width;
    else
        this->maxframe = 1;
}

F2C::uint Animation::getFrameWidth() const{
    if(this->maxframe < 2)
        return this->getSprWidth();
    else
        return this->getSprWidth()/this->maxframe;

}

void Animation::nextFrame(){
    if(this->frame+1 >= this->maxframe)
        this->end = true;
    else
        this->frame = (this->frame+1) % this->maxframe;
}

void Animation::update(){
    if(this->maxframe < 2)
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

    this->ani_src_rect.set( this->frame*(this->getSprWidth()/this->maxframe),
                        0,
                        this->getSprWidth()/this->maxframe,
                        this->getSprHeight());
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

ArraySpriteAnimation::ArraySpriteAnimation(const F2C::Bitmap* bitmap):
    ArraySprite(bitmap)
{}

F2C::uint ArraySpriteAnimation::getSprWidth() const{
    return this->getTexWidth();
}
F2C::uint ArraySpriteAnimation::getSprHeight() const{
    return this->getTexHeight();
}

void ArraySpriteAnimation::update(){
    this->Animation::update();
    for(size_t i = 0;i < this->elements.size();i++)
        this->elements[i].src_rect = this->ani_src_rect;
}

void ArraySpriteAnimation::refreshSrcRect(){
    for(size_t i = 0;i < this->elements.size();i++)
        this->elements[i].src_rect = this->ani_src_rect;
}
