#include <Fantasy2C/Window.hpp>

namespace F2C{

Window::Window():
    FPS(0.0f),
	startTime(0.0f),
	startTick(0.0f),
	activTime(0.0f),
	frames(0)
{}

Window::Window(std::string title,uint width,uint height, int bits, bool fullscreen):
    FPS(0.0f),
	startTime(0.0f),
	startTick(0.0f),
	activTime(0.0f),
	frames(0)
{
    this->CreateGLWindow(title,width,height,bits,fullscreen);
    this->InitGL();
}

void Window::UpdateGLScreen(){
   this->frames++;
   glfwSwapBuffers();
   this->activTime = glfwGetTime();
   if( (this->activTime-this->startTime) > 1.0 || this->frames == 0 ){
      this->FPS = static_cast<double>(this->frames) / (this->activTime-this->startTime);
      this->startTime = this->activTime;
      this->frames = 0;
   }
}

void Window::ReSize(uint wndwidth, uint wndheight,uint screenwidth,uint screenheight){
	if(wndheight < 1)
		wndheight = 1;
    if(screenheight < 1)
         screenheight = 1;

    glfwSetWindowSize(wndwidth,wndheight);
	glViewport(0,wndheight-screenheight,screenwidth,screenheight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,screenwidth,screenheight,0,INT_MIN+1,INT_MAX-1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Window::InitGL(){
	glAlphaFunc(GL_GREATER, 0.000f);
	glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
}

void Window::ClearGLScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
}

void Window::ShutdownGLWindow(){
	glfwTerminate();
}


bool Window::CreateGLWindow(std::string title,uint width,uint height, int bits, bool fullscreen){
   if(! (glfwInit()))
      return false;

   if (height == 0) height = 1;

	this->frames = 0;
	this->FPS = 0.0f;
	this->activTime = 0.0f;
	this->startTime = glfwGetTime();
	this->startTick = 0.0f;

    this->showmouse = false;

	int rgba[4] = {0,0,0,0};
	if(bits == 8){
	   rgba[0] = 3;
	   rgba[1] = 3;
	   rgba[2] = 2;
   }else if(bits == 12){
	   rgba[0] = 4;
	   rgba[1] = 4;
	   rgba[2] = 4;
   }else if(bits == 16){
	   rgba[0] = 5;
	   rgba[1] = 6;
	   rgba[2] = 5;
   }else if(bits == 24){
      rgba[0] = 8;
      rgba[1] = 8;
      rgba[2] = 8;
   }else if(bits == 36){
      rgba[0] = 12;
      rgba[1] = 12;
      rgba[2] = 12;
   }else if(bits == 42){
      rgba[0] = 14;
      rgba[1] = 14;
      rgba[2] = 14;
   }else if(bits == 48){
      rgba[0] = 16;
      rgba[1] = 16;
      rgba[2] = 16;
   }else{
      rgba[0] = 8;
      rgba[1] = 8;
      rgba[2] = 8;
      rgba[3] = 8;
   }

	int mode = (fullscreen)? GLFW_FULLSCREEN : GLFW_WINDOW;
	this->showmouse = (fullscreen)? false : true;

   if(! (glfwOpenWindow(
           width, height,     // Width and height of window
           rgba[0], rgba[1], rgba[2],           // Number of red, green, and blue bits for color buffer
           rgba[3],                 // Number of bits for alpha buffer
           bits,              // Number of bits for depth buffer (Z-buffer)
           bits,              // Number of bits for stencil buffer
           mode        // Window or Fullscreen mode
         )
   )){
      glfwTerminate();
      return false;
   }

   glfwSetWindowTitle(title.c_str());

   this->ReSize(width,height,width,height);

	return true;
}

void Window::setWindowPosition(int x,int y){glfwSetWindowPos(x,y);}
void Window::setWindowSize(uint wndwidth, uint wndheight){glfwSetWindowSize(wndwidth,wndheight);}
void Window::setWindowTitle(std::string title){glfwSetWindowTitle(title.c_str());}

void Window::setWindowHint(WindowProperty::ParamWindow paramwindow,int value){
   glfwOpenWindowHint(paramwindow,value);
}

int Window::getWindowParam(WindowProperty::ParamWindow param){
   return glfwGetWindowParam(param);
}

void Window::getWindowSize(int* width,int* height){glfwGetWindowSize( width, height );}

void Window::setTime(double time){glfwSetTime(time);}
double Window::getTime(){return glfwGetTime();}
void Window::Sleep(double time){glfwSleep(time);}

void Window::startTicks(){this->startTick = glfwGetTime();}
double Window::getTicks(){return glfwGetTime()-this->startTick;}

void Window::getSize(int* wndwidth, int* wndheight,uint* screenwidth,uint* screenheight){
   int params[4];
   glGetIntegerv(GL_VIEWPORT,params);
   if(screenwidth)
        *screenwidth = params[2];
   if(screenheight)
        *screenheight = params[3];
   glfwGetWindowSize(wndwidth,wndheight);
}

void Window::getScreenSize(uint* screenwidth,uint* screenheight){
   int params[4];
   glGetIntegerv(GL_VIEWPORT,params);
   if(screenwidth)
        *screenwidth = params[2];
   if(screenheight)
        *screenheight = params[3];
}

double Window::getFPS(){return this->FPS;}
uint Window::getFrame(){return this->frames;}

void Window::showMouseCursor(bool show){
    if(show)
        glfwEnable(GLFW_MOUSE_CURSOR);
    else
        glfwDisable(GLFW_MOUSE_CURSOR);
    this->showmouse = show;
}

bool Window::getShowMouseCursor(){
    return this->showmouse;
}

};


