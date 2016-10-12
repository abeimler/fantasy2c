#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Sprite.hpp>

int main(){

    //get Instance
    F2C::Window& WinApp = *F2C::Window::getInstance();

    //Window title
    std::string title = "Fantasy2C Simple: Bitmap and Sprite";

    //Window size
    F2C::uint wndWidth = 800;
    F2C::uint wndHeight = 600;

    //Window color depth
    F2C::uint wndBPP = 32;

    //Fullscreen On/Off
    bool fullscreen = false;

    WinApp.setWindowHint(F2C::WindowProperty::NoResize,true);  //set Window Option: Window No Resize = true
    WinApp.CreateGLWindow(title.c_str(),wndWidth,wndHeight,wndBPP,fullscreen);  //create Window
    WinApp.setWindowPosition(160,120); //set Window Pos.

    WinApp.InitGL(); //init OpenGL
    F2C::LogError::ClearLog(); //clear LogFile

    F2C::Bitmap* bitmap = new F2C::Bitmap;
    try{
        bitmap->loadFile("logo.jpg"); //load Image into Bitmap
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    F2C::Sprite sprLogo;
    sprLogo.setBitmap(bitmap); //load Bitmap into Sprite

    delete bitmap;

    //set Coord.
    sprLogo.x = wndWidth/2 - sprLogo.getTexWidth()/2;
    sprLogo.y = wndHeight/2 - sprLogo.getTexHeight()/2;
    sprLogo.tone.set(155,55,25); //set ColorTone

    bool quit = false;
    while(!quit){
        WinApp.ClearGLScene(); //clear Screen

        //Rendering

        sprLogo.render();

        //End Rendering

        WinApp.UpdateGLScreen(); //update Screen

        if(! WinApp.getWindowParam(F2C::WindowProperty::Open)){  //Window not open
            quit = true;
        }
    }

    //shutdown Window
	WinApp.ShutdownGLWindow();

    return 0;
}
