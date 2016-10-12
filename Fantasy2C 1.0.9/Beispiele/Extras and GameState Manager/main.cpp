#include "GameStates.hpp"
#include "GameRunState.hpp"

int main(int argc,const char** argv){

    //Window Size
    int wndWidth = 800;
    int wndHeight = 600;

    std::string title = "Fantasy2C Simple: Extras and GameState Manager"; //Window Title
    bool fullscreen = false; //Fullscreen On/OFF
    F2C::uint wndBits = 32; //Color depth

    //init Reference to GameEngine Singletone Class
    GameEngine& GameEngineApp = *GameEngine::getInstance();

    //Create Window
    GameEngineApp.Init(title,wndWidth,wndHeight,wndBits,fullscreen);

    //Set Settings
    GameEngineApp.framerate = 60.0f; //Maximale Framerate(FPS)
    GameEngineApp.renderingWholeStack = true; //Rendering all States ON/OFF
    GameEngineApp.showFPS = true; //Show FPS in Title Bar Window
    GameEngineApp.MaxFramerateON = true; //Use maximale Framerate ON/OFF
    GameEngineApp.useESC = false; //Use ESC to Quit Program

    //init Main State (with new operator)
    GameEngineApp.PushState(new GameRunState);

    //Gameloop
    while(GameEngineApp.Running()){ //Winodw is running?

        GameEngineApp.HandleEvents(); //update EventHandle(press ESC,framerate slow down)

        GameEngineApp.Update(); //update State

        GameEngineApp.Render(); //rendering State(s)
    }

    GameEngineApp.Cleanup(); //Clean up Window and States

    return 0;
}
