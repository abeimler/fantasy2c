#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/Font.hpp>
#include <Fantasy2C/FontSprite.hpp>

int main(){

    //get Instance
    F2C::Window WinApp;

    //Window title
    std::string title = "Fantasy2C Simple: TTFFont and FontSprite";

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
        fontfile->loadFile("Arial.ttf",42); //load TTF into TTFFont,fontsize: 42
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    F2C::FontSprite fsprHallo;
    fsprHallo.setBitmap(&(fontfile->getBitmap())); //load Bitmapfont into Sprite

    delete fontfile;

    //set coord.
    fsprHallo.x = wndWidth/2-180;
    fsprHallo.y = wndHeight/2-50;
    //set vertices Color
    fsprHallo.vColor[0].set(255,0,255);
    fsprHallo.vColor[1].set(50,0,255);
    fsprHallo.vColor[2].set(0,0,255);
    fsprHallo.vColor[3].set(0,0,255);

    //add text
    fsprHallo.addText(0,0,320,78,"Hallo Welt");
    //set zoom factor
    fsprHallo.zoom_x = 1.5f;
    fsprHallo.zoom_y = 1.5f;

    bool quit = false;
    while(!quit){
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
