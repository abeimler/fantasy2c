#include <iostream>
#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Input.hpp>
#include <Fantasy2C/SimpleSprite.hpp>
#include <Fantasy2C/FontSprite.hpp>
#include <Fantasy2C/Font.hpp>

int main(){

    //get Instance
    F2C::Window& WinApp = *F2C::Window::getInstance();

    //Window title
    std::string title = "Fantasy2C Simple: Max FPS";

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
    F2C::TTFFont* fontfile = new F2C::TTFFont;
    try{
        fontfile->loadFile("Arial.ttf",28); //load TTF into TTFFont,fontsize: 28
        bitmap->loadFile("logo.jpg"); //load Image into Bitmap
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    F2C::SimpleSprite ssprLogo;
    ssprLogo.setBitmap(bitmap); //load Bitmap into Sprite

    F2C::FontSprite fsprFPS;
    fsprFPS.setBitmap(&(fontfile->getBitmap())); //load Bitmapfont into Sprite

    delete bitmap;
    delete fontfile;

    //set Coord.
    ssprLogo.x = wndWidth/2 - ssprLogo.getTexWidth()/2;
    ssprLogo.y = wndHeight/2 - ssprLogo.getTexHeight()/2;

    bool quit = false;
    while(!quit){
        WinApp.startTicks(); //start Timer

        //Game Update

        std::stringstream ssFPS (std::stringstream::in | std::stringstream::out);
        ssFPS << title << " :: " << WinApp.getFPS() << " FPS";
        fsprFPS.clearTexts();
        fsprFPS.addText(8,8,640,48,ssFPS.str());

        //End Game Update

        WinApp.ClearGLScene(); //clear Screen

        //Rendering

        ssprLogo.render();
        fsprFPS.render();

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
