#include <Fantasy2C/Input.hpp>

namespace F2C{

Input::Input():
    mousewheelpos(glfwGetMouseWheel()),
    last_frame(0)
{
   glfwInit();

   //glfwEnable(GLFW_STICKY_KEYS);
   glfwEnable(GLFW_SYSTEM_KEYS);
   glfwDisable(GLFW_AUTO_POLL_EVENTS);
   //glfwEnable(GLFW_STICKY_MOUSE_BUTTONS);

   memset(this->keys,0,319*sizeof(bool));
   memset(this->old_keys,0,319*sizeof(bool));
   memset(this->presskeys,0,319*sizeof(bool));
   memset(this->mouse,0,8*sizeof(bool));
   memset(this->old_mouse,0,8*sizeof(bool));
   memset(this->pressmouse,0,8*sizeof(bool));
}

void Input::update(int frame){
    this->updatePress();
    this->updateRepeat(frame);
}

void Input::update(){
    this->updatePress();
    this->updateRepeat();
}

void Input::updateRepeat(int frame){
    if(frame == this->last_frame)
        return;

    this->updateRepeat();

    this->last_frame = frame;
}

void Input::updateRepeat(){
    glfwPollEvents();
    for(size_t i = 0;i < 319;i++){
        bool press = (glfwGetKey(i) == GLFW_PRESS);
        if(press){
            if (!this->old_keys[i])
                this->keys[i] = true;
            else
                this->keys[i] = false;
        }else{
            this->keys[i] = false;
        }
        this->old_keys[i] = press;
    }
    for(size_t i = GLFW_MOUSE_BUTTON_1;i <= GLFW_MOUSE_BUTTON_LAST;i++){
        bool press = (glfwGetMouseButton(i) == GLFW_PRESS);
        if(press){
            if (!this->old_mouse[i])
                this->mouse[i] = true;
            else
                this->mouse[i] = false;
        }else{
            this->mouse[i] = false;
        }
        this->old_mouse[i] = press;
    }
}

void Input::updatePress(){
    glfwPollEvents();
    memset(this->presskeys,0,319*sizeof(bool));
    memset(this->pressmouse,0,8*sizeof(bool));
    for(size_t i = 0;i < 319;i++){
        bool press = (glfwGetKey(i) == GLFW_PRESS);
        if(press)
            this->presskeys[i] = true;
    }
    for(size_t i = GLFW_MOUSE_BUTTON_1;i <= GLFW_MOUSE_BUTTON_LAST;i++){
        bool press = (glfwGetMouseButton(i) == GLFW_PRESS);
        if(press)
            this->pressmouse[i] = true;
    }
}

void Input::getMousePos(int* x,int* y){
   glfwGetMousePos(x,y);
}

bool Input::getPressKey(char ckey){
   return this->presskeys[static_cast<unsigned char>(ckey)];
}

bool Input::getPressKey(KeyboardEvent::Keyboard key){
    return this->presskeys[static_cast<size_t>(key)];
}

bool Input::getRepeatKey(char ckey){
   return this->keys[static_cast<unsigned char>(ckey)];
}

bool Input::getRepeatKey(KeyboardEvent::Keyboard key){
    return this->keys[static_cast<size_t>(key)];
}

bool Input::getPressMouse(MouseEvent::Mouse mousekey){
    return this->pressmouse[static_cast<size_t>(mousekey)];
}

bool Input::getRepeatMouse(MouseEvent::Mouse mousekey){
   return this->mouse[static_cast<size_t>(mousekey)];
}

const bool* Input::getRepeatKeyArray(){
    return this->keys;
}
const bool* Input::getPressKeyArray(){
    return this->presskeys;
}

size_t Input::getSizeKeyArray(){
    return 319;
}

const bool* Input::getRepeatMouseArray(){
    return this->mouse;
}
const bool* Input::getPressMouseArray(){
    return this->pressmouse;
}

size_t Input::getSizeMouseArray(){
    return 8;
}

int Input::getMouseWheel(){
   return glfwGetMouseWheel();
}

void Input::setMousePos(int x,int y){
   glfwSetMousePos(x,y);
}

void Input::setMouseWheel(int pos){
   glfwSetMouseWheel(pos);
}

bool Input::getMouseWheelDown(){
    if(glfwGetMouseWheel() < this->mousewheelpos){
        this->mousewheelpos = glfwGetMouseWheel();
        return true;
    }
    return false;
}
bool Input::getMouseWheelUp(){
    if(glfwGetMouseWheel() > this->mousewheelpos){
        this->mousewheelpos = glfwGetMouseWheel();
        return true;
    }
    return false;
}

int Input::getJoystickParam(JoystickEvent::Joystick joy, JoystickEvent::ParamJoystick param ){
    return glfwGetJoystickParam(joy,param);
}
int Input::getJoystickPos(JoystickEvent::Joystick joy, float *pos, int numaxes ){
    return glfwGetJoystickPos(joy,pos,numaxes);
}
int Input::getJoystickButtons(JoystickEvent::Joystick joy, uint8* buttons, int numbuttons ){
    return glfwGetJoystickButtons(joy,buttons,numbuttons);
}


};


