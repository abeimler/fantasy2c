#include "basic.h"

namespace F2C{

InKey* InKey::_instance = NULL;

InKey& InKeyApp = *InKey::getInstance(); //get Instance

InKey* InKey::getInstance(){
    if(! _instance)
        _instance = new InKey;

    return _instance;
}

InKey::InKey(){
    this->last_frame = 0;
    memset(this->mouse,0,9*sizeof(bool));
    memset(this->old_mouse,0,9*sizeof(bool));
    memset(this->key,0,319*sizeof(bool));
    memset(this->old_key,0,319*sizeof(bool));

    this->mousewheelpos = F2C::Input::getInstance()->getMouseWheel();
}



void InKey::update(){
    //update input,keys array and mouse array
    if(this->last_frame == F2C::Window::getInstance()->getFrame())
        return;
    F2C::Input::getInstance()->update();
    for(int key = 0;key < 319;key++){
        bool press = (key > 256)? F2C::Input::getInstance()->getPressKey(static_cast<F2C::KeyboardEvent::Keyboard>(key)) : F2C::Input::getInstance()->getPressKey(key);
        if(press){
            if (!this->old_key[key]){
                this->key[key] = true;
            }else{
                this->key[key] = false;
            }
        }else{
            this->key[key] = false;
        }
        this->old_key[key] = press;
    }
    for(int key = 0;key < 9;key++){
        bool press = F2C::Input::getInstance()->getPressMouse(static_cast<F2C::MouseEvent::Mouse>(key));
        if(press){
            if (!this->old_mouse[key]){
                this->mouse[key] = true;
            }else{
                this->mouse[key] = false;
            }
        }else{
            this->mouse[key] = false;
        }
        this->old_mouse[key] = press;
    }
    this->last_frame = F2C::Window::getInstance()->getFrame();
}

bool InKey::getTriggerKey(int key){
    return this->key[static_cast<size_t>(key)];
}

bool InKey::getPressKey(int key){
    if(key > 255)
        return F2C::Input::getInstance()->getPressKey(static_cast<F2C::KeyboardEvent::Keyboard>(key));
    else
        return F2C::Input::getInstance()->getPressKey(key);
}

bool InKey::getTriggerKey(F2C::KeyboardEvent::Keyboard key){
    return this->key[static_cast<size_t>(key)];
}

bool InKey::getPressKey(F2C::KeyboardEvent::Keyboard key){
    return F2C::Input::getInstance()->getPressKey(key);
}

bool InKey::getTriggerMouse(F2C::MouseEvent::Mouse key){
    return this->mouse[static_cast<size_t>(key)];
}

bool InKey::getPressMouse(F2C::MouseEvent::Mouse key){
    return F2C::Input::getInstance()->getPressMouse(key);
}

bool InKey::getMouseWheelDown(){
    if(F2C::Input::getInstance()->getMouseWheel() < this->mousewheelpos){
        this->mousewheelpos = F2C::Input::getInstance()->getMouseWheel();
        return true;
    }
    return false;
}
bool InKey::getMouseWheelUp(){
    if(F2C::Input::getInstance()->getMouseWheel() > this->mousewheelpos){
        this->mousewheelpos = F2C::Input::getInstance()->getMouseWheel();
        return true;
    }
    return false;
}

const bool* InKey::getMouseArray(){
    return this->mouse;
}

const bool* InKey::getKeyArray(){
    return this->key;
}

}
