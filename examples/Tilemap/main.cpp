#include "Tilemap.hpp"

int main(){
    F2C::Window WinApp;
    F2C::Input InApp;

    //Window title
    std::string title = "Fantasy2C Simple: Tilemap and Tileset";

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

    Tileset tileset;
    tileset.loadTileset("wood.png");
    tileset.addAniTile("water.png");
    tileset.addAniTile("fire.png");

    Tilemap tilemap (F2C::Viewport (0,0,800,600),40,40,2);
    tilemap.loadTileset(tileset);

    tilemap.fillTileLayer(0,1);

    tilemap.fillAniTileRect(4,4,0  ,6,7, 0); //water
    tilemap.setAniTileid(6,14,1,1); //fire

    //tree
    tilemap.setTileArrayRect(9,5,1, 4,5 ,40);
    tilemap.setTileArrayRect(1,7,1, 4,5 ,40);

    //tree 2
    tilemap.setTileArrayRect(13,8,1, 2,4 ,21);
    tilemap.setTileArrayRect(2,3,1, 2,4 ,21);

    //house
    tilemap.setTileArrayRect(5,9,1, 5,4 ,8);

    bool quit = false;
    while(!quit){
        //Game Update
        InApp.update();

        int movespeed = 4;
        if(InApp.getPressKey(F2C::KeyboardEvent::Up)){
            tilemap.oy -= movespeed;
        }else if(InApp.getPressKey(F2C::KeyboardEvent::Down)){
            tilemap.oy += movespeed;
        }else if(InApp.getPressKey(F2C::KeyboardEvent::Right)){
            tilemap.ox += movespeed;
        }else if(InApp.getPressKey(F2C::KeyboardEvent::Left)){
            tilemap.ox -= movespeed;
        }
        tilemap.ox = std::max<int>(0,tilemap.ox);
        tilemap.oy = std::max<int>(0,tilemap.oy);
        tilemap.ox = std::min<int>((tilemap.getWidth()*tileset.getTileWidth())-wndWidth,tilemap.ox);
        tilemap.oy = std::min<int>((tilemap.getHeight()*tileset.getTileHeight())-wndHeight,tilemap.oy);
        tilemap.update();

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
                WinApp.Sleep(0.0001f); //sleep
        }while(WinApp.getTicks() <= 1.0f/framerate); //get Time(in sec) <= FPS
        WinApp.startTicks(); //restart Timer
    }

    //shutdown Window
	WinApp.ShutdownGLWindow();

    return 0;
}
