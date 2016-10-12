#include "GameStates.hpp"
#include "GameRunState.hpp"

int main(int argc,const char** argv){
    //Windowd Size
    int wndWidth = 800;
    int wndHeight = 600;

    //Title, fullscreen and color depth
    std::string title = "Fantasy2C Simple: Extras and GameState";
    bool fullscreen = false;
    F2C::uint wndBits = 32;

    //Create Window App
    Engine::Game.Init(title,wndWidth,wndHeight,wndBits,fullscreen);

    //Settings
    Engine::Game.framerate = 60.0f;
    Engine::Game.renderingWholeStack = true;
    Engine::Game.showFPS = true;
    Engine::Game.MaxFramerateON = true;
    Engine::Game.useESC = true;

    Engine::Game.showMouse = true;
    Engine::Game.loadMouseBitmap("mouse.png");

    //Push back a Scene on Game State
    Engine::Game.PushState(new GameRunState);

    //Game Loop
    while(Engine::Game.Running()){
        //update Game states
        Engine::Game.UpdateState();

        //Windows Handle
        Engine::Game.HandleEvents();

        //Game update
        Engine::Game.Update();

        //Game Rendering
        Engine::Game.Render();

    }

    //Clean Window App
    Engine::Game.Cleanup();

    return 0;
}
