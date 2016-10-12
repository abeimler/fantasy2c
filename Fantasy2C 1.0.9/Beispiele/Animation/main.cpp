#include "Animation.hpp"

int main(){

    //get Instance
    F2C::Window& WinApp = *F2C::Window::getInstance();

    //Window title
    std::string title = "Fantasy2C Simple: Animation";

    //Window size
    F2C::uint wndWidth = 800;
    F2C::uint wndHeight = 600;

    //Window color depth
    F2C::uint wndBPP = 32;

    //Fullscreen On/Off
    bool fullscreen = false;

    //set Maximum FPS
    double framerate = 60.0f;

    WinApp.setWindowHint(F2C::WindowProperty::NoResize,true);  //set Window Option: Window No Resize = true
    WinApp.CreateGLWindow(title.c_str(),wndWidth,wndHeight,wndBPP,fullscreen);  //create Window
    WinApp.setWindowPosition(160,120); //set Window Pos.

    WinApp.InitGL(); //init OpenGL
    F2C::LogError::ClearLog(); //clear LogFile

    F2C::Bitmap* bitmap = new F2C::Bitmap;
    try{
        bitmap->loadFile("explosion.png"); //load Image into Bitmap
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    Animation aniExplosion;
    aniExplosion.setBitmap(bitmap); //load Bitmap into Sprite

    delete bitmap;

    //set animation settings
    aniExplosion.framepertime = true; //animation by timer
    aniExplosion.frameperwidth = 5; //frames per width
    aniExplosion.frameperheight = 3; //frames per height
    aniExplosion.maxframe = 12; //numbers of frames
    aniExplosion.endless = true; //endless animation

    //set Coord.
    aniExplosion.x = wndWidth/2 - aniExplosion.getFrameWidth()/2;
    aniExplosion.y = wndHeight/2 - aniExplosion.getFrameHeight()/2;

    bool quit = false;
    while(!quit){
        WinApp.startTicks(); //start Timer

        //Game Update

        aniExplosion.update();

        //End Game Update

        WinApp.ClearGLScene(); //clear Screen

        //Rendering

        aniExplosion.render();

        //End Rendering

        WinApp.UpdateGLScreen(); //update Screen

        //FPS brake
        do{
            if(! WinApp.getWindowParam(F2C::WindowProperty::Open)){  //Window not open
                quit = true;
            }

            if(WinApp.getTicks() <= 1.0f/framerate)
                F2C::Window::getInstance()->Sleep(0.001f); //sleep
        }while(WinApp.getTicks() <= 1.0f/framerate); //get Time(in sec) <= FPS
    }

    //shutdown Window
	WinApp.ShutdownGLWindow();

    return 0;
}
