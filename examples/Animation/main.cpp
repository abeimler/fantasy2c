#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Input.hpp>
#include "Animation.hpp"

int main(){

    F2C::Window WinApp;

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

    SimpleSpriteAnimation aniExplosion;

    F2C::Bitmap* bitmap = new F2C::Bitmap;
    try{
        bitmap->loadFile("explosion.png"); //load Image into Bitmap
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }
    aniExplosion.setBitmap(bitmap); //load Bitmap into Sprite
    delete bitmap;

    //set animation settings
    aniExplosion.framepertime = true; //animation by timer
    aniExplosion.setFrameperWidth(5); //frames per width
    aniExplosion.setFrameperHeight(3); //frames per height
    aniExplosion.maxframe = 12; //absolute frames
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
                WinApp.Sleep(0.001f); //sleep
        }while(WinApp.getTicks() <= 1.0f/framerate); //get Time(in sec) <= FPS
    }

    //shutdown Window
	WinApp.ShutdownGLWindow();

    return 0;
}
