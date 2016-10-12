#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Input.hpp>
#include <Fantasy2C/FontSprite.hpp>
#include <Fantasy2C/Font.hpp>

int main(){

    //init Window and Input App
    F2C::Window WinApp;
    F2C::Input InApp;

    //Window title
    std::string title = "Fantasy2C Simple: Input";

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

    F2C::TTFFont* fontfile = new F2C::TTFFont;
    try{
        fontfile->loadFile("Arial.ttf",52); //load TTF into TTFFont,fontsize: 52
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    F2C::FontSprite fsprHallo;
    fsprHallo.setBitmap(fontfile); //load Bitmapfont into Sprite

    delete fontfile;

    //set coord.
    fsprHallo.x = wndWidth/2-180;
    fsprHallo.y = wndHeight/2-180;

    //add text
    fsprHallo.addText(0,0,"Press to set Color:");
    fsprHallo.addText(0,50,"1: Red");
    fsprHallo.addText(0,100,"2: Green");
    fsprHallo.addText(0,150,"3: Blue");
    fsprHallo.addText(0,200,"4: Yellow");
    fsprHallo.addText(0,250,"5: Violet");
    fsprHallo.addText(0,300,"6: White");

    bool quit = false;
    while(!quit){
        InApp.update(); //update Input
        WinApp.startTicks(); //start Timer

        //Game Update


        if(InApp.getPressKey('1'))
            fsprHallo.setColor(255,0,0);
        else if(InApp.getPressKey('2'))
            fsprHallo.setColor(0,255,0);
        else if(InApp.getPressKey('3'))
            fsprHallo.setColor(0,0,255);
        else if(InApp.getPressKey('4'))
            fsprHallo.setColor(255,255,0);
        else if(InApp.getPressKey('5'))
            fsprHallo.setColor(255,0,255);
        else if(InApp.getPressKey('6'))
            fsprHallo.setColor(255,255,255);

        //End Game Update

        WinApp.ClearGLScene(); //clear Screen

        //Rendering

        fsprHallo.render();

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
