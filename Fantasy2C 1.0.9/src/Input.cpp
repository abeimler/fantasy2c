#include "Input.hpp"

namespace F2C{

Input* Input::_instance = NULL;

Input* Input::getInstance(){
   if (!Input::_instance)
      Input::_instance = new Input;
   return Input::_instance;
}

Input::Input():
	repeaton(false)
{
   memset(this->keys,0,319*sizeof(bool));
   memset(this->presskeys,0,319*sizeof(bool));
}

bool Input::InitInput(){
   if(! (glfwInit()))
      return false;

   //glfwEnable(GLFW_STICKY_KEYS);
   glfwEnable(GLFW_SYSTEM_KEYS);
   glfwDisable(GLFW_AUTO_POLL_EVENTS);
   //glfwEnable(GLFW_KEY_REPEAT);
   //glfwEnable(GLFW_STICKY_MOUSE_BUTTONS);

   glfwSetKeyCallback( (GLFWkeyfun)Input::keyhandler );
   memset(this->keys,0,319*sizeof(bool));
   memset(this->presskeys,0,319*sizeof(bool));
   this->repeaton = false;

   return true;
}

void Input::update(){
    memset(this->keys,0,319*sizeof(bool));
    memset(this->presskeys,0,319*sizeof(bool));
    glfwPollEvents();
    for(size_t i = 0;i < 319;i++){
        if(glfwGetKey(i) == GLFW_PRESS)
            this->presskeys[i] = true;
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
    return (glfwGetMouseButton(static_cast<size_t>(mousekey)) == GLFW_PRESS)? true : false;
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

int Input::getMouseWheel(){
   return glfwGetMouseWheel();
}

void Input::setMousePos(int x,int y){
   glfwSetMousePos(x,y);
}

void Input::setMouseWheel(int pos){
   glfwSetMouseWheel(pos);
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

void Input::setRepeatMode(bool on){
    if(on)
        glfwEnable(GLFW_KEY_REPEAT);
    else
        glfwDisable(GLFW_KEY_REPEAT);
    this->repeaton = on;
}

bool Input::getRepeatMode(){
    return this->repeaton;
}

void GLFWCALL Input::keyhandler( int key, int action ){
    if(action == GLFW_PRESS)
        Input::getInstance()->keys[key] = true;
}

};


