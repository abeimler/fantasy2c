#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Sprite.hpp>
#include <Fantasy2C/Input.hpp>

int main(){
    F2C::Window WinApp;
    F2C::Input InApp;

    //Window title
    std::string title = "Fantasy2C Simple: Bitmap,Sprite and Blending Effect";

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

    F2C::Bitmap* bitLogo = new F2C::Bitmap;
    F2C::Bitmap* bitLight = new F2C::Bitmap;
    F2C::Bitmap* bitMask = new F2C::Bitmap;
    try{
        bitLogo->loadFile("logo.jpg"); //load Image into Bitmap
        bitLight->loadFile("light.png");
        bitMask->loadFile("mask.png");
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    F2C::Sprite sprLogo;
    F2C::Sprite sprLight;
    F2C::Sprite sprMask;
    sprLogo.setBitmap(bitLogo); //load Bitmap into Sprite
    sprLight.setBitmap(bitLight);
    sprMask.setBitmap(bitMask);

    delete bitLogo;
    delete bitLight;
    delete bitMask;

    //set Coord.
    sprLogo.x = wndWidth/2 - sprLogo.getTexWidth()/2;
    sprLogo.y = wndHeight/2 - sprLogo.getTexHeight()/2;

    sprLight.x = sprLogo.x;
    sprLight.y = sprLogo.y;
    sprMask.x = sprLogo.x;
    sprMask.y = sprLogo.y;

    sprMask.blend_type = F2C::BlendType::mask;
    sprLight.blend_type = F2C::BlendType::light;
    sprLight.setColor(255,25,55,255);

    bool quit = false;
    while(!quit){
        WinApp.ClearGLScene(); //clear Screen
        InApp.update();

        if(InApp.getPressKey('1')){
            sprLogo.render();
            sprLight.render();
        }else if(InApp.getPressKey('2')){
            sprLogo.render();
            sprMask.render();
        }else if(InApp.getPressKey('3')){
            sprLogo.tone.set(255,55,25); //set ColorTone
            sprLogo.render();
        }else{
            sprLogo.tone.set(0,0,0); //clear ColorTone
            sprLogo.render();
        }

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
