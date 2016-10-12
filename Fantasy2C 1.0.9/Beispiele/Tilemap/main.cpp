#include <Fantasy2C/Window.hpp>
#include <Fantasy2C/ArraySprite.hpp>
#include "Tilemap.hpp"

int random(int lowest_number, int highest_number){
    if(lowest_number == highest_number)
        return lowest_number;
    srand(static_cast<F2C::uint>(floor(F2C::Window::getInstance()->getTime()*time(NULL))));
    int range = highest_number - lowest_number + 1;
    if(range == 0)
        return 0;
    else
        return (rand() % range) + lowest_number;
}

int main(){

    //get Instance
    F2C::Window& WinApp = *F2C::Window::getInstance();

    //Window title
    std::string title = "Fantasy2C Simple: Tileset";

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
        bitmap->loadFile("tileset.png"); //load Image into Bitmap
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }

    Tileset tileset;
    tileset.setBitmap(*bitmap,32,32); //load Bitmap into Sprite, set tilewidth and tileheight

    delete bitmap;

    Tilemap tilemap (50,50,3); //set map size 50x50x3 (tiles)
    tilemap.setTileset(tileset); //set tileset
    tilemap.viewport.clip_rect.set(0,0,wndWidth,wndHeight); //set viewport rect

    //set ids/tiles

    //tile: grass
    //set all tiles, in layer 0
    for(size_t x = 0;x < tilemap.getWidth();x++){
        for(size_t y = 0;y < tilemap.getHeight();y++){
            tilemap.setID(x,y,0,1); //set ID: 1
        }
    }

    //tile: flower
    //set flowers in random positions, in layer 1
    size_t nflowers = random(10,25); //numbers of flowers
    for(size_t i = 0;i < nflowers;i++){
        size_t x = random(0,25);
        size_t y = random(0,19);
        tilemap.setID(x,y,1,2); //set ID: 2
    }

    //tile: tree
    //set trees in random position, in layer 2
    size_t tx = static_cast<size_t>(random(8,15));
    size_t ty = static_cast<size_t>(random(4,11));

    //set ID:  6, 7, 8
    //        12,13,14
    //        18,19,20
    //        24,25,26
    tilemap.setID(tx,ty,   2,6);  tilemap.setID(tx+1,ty,   2,7);  tilemap.setID(tx+2,ty,   2,8);
    tilemap.setID(tx,ty+1, 2,12); tilemap.setID(tx+1,ty+1, 2,13); tilemap.setID(tx+2,ty+1, 2,14);
    tilemap.setID(tx,ty+2, 2,18); tilemap.setID(tx+1,ty+2, 2,19); tilemap.setID(tx+2,ty+2, 2,20);
    tilemap.setID(tx,ty+3, 2,24); tilemap.setID(tx+1,ty+3, 2,25); tilemap.setID(tx+2,ty+3, 2,26);


    bool quit = false;
    while(!quit){
        WinApp.startTicks(); //start Timer

        //Game Update

        //End Game Update

        WinApp.ClearGLScene(); //clear Screen

        //Rendering

        tilemap.render();

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
