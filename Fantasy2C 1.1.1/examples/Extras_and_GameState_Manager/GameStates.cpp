#include "GameStates.hpp"

GameEngine::GameEngine():
    running(false),
	lastFPS(0.0f),
	fullscreen(false),
    MaxFramerateON(true),
    framerate(60.0f),
    useESC(true),
    showFPS(true),
    renderingWholeStack(true)
{}

void GameEngine::Init(std::string title, F2C::uint width, F2C::uint height, F2C::uint bpp, bool fullscreen){
    this->title = title;
    this->running = true;

    //set defaults
	this->MaxFramerateON = true;
	this->framerate = 60.0f;
	this->useESC = true;
	this->lastFPS = 0.0f;
	this->showFPS = true;
	this->renderingWholeStack = true;
	this->fullscreen =  fullscreen;

    this->WinApp.setWindowHint(F2C::WindowProperty::NoResize,true);  //set Option:Window No Resize = true
    this->WinApp.CreateGLWindow(this->title.c_str(),width,height,bpp,fullscreen);  //create Window
    this->WinApp.setWindowPosition(160,120);

    this->WinApp.InitGL();
    F2C::ShaderGL::InitGLShader();
    F2C::LogError::ClearLog();

	this->WinApp.startTicks();
}

void GameEngine::Cleanup(){
	// cleanup the all states
	while ( !this->states.empty() ) {
	    if(this->states.back()){
            this->states.back()->Cleanup();
            delete this->states.back();
	    }
		this->states.pop_back();
	}

	// shutdown Window
	this->WinApp.ShutdownGLWindow();
}

void GameEngine::ChangeState(GameState* state) {
	// cleanup the current state
	while ( !this->states.empty() ) {
		if(this->states.back()){
            this->states.back()->Cleanup();
            delete this->states.back();
	    }
		this->states.pop_back();
	}

	// store and init the new state
	this->states.push_back(state);
	if(this->states.back())
        this->states.back()->Init();
}

void GameEngine::PushState(GameState* state){
	// store and init the new state
	this->states.push_back(state);
	if(this->states.back())
        this->states.back()->Init();
}

void GameEngine::PopState(){
	// cleanup the current state
	if ( !this->states.empty() ){
		if(this->states.back()){ //clearup and delete
            this->states.back()->Cleanup();
            delete this->states.back();
	    }
		this->states.pop_back();
	}
}


void GameEngine::HandleEvents() {
    if(this->lastFPS != this->WinApp.getFPS()){
        if(this->showFPS){
            std::stringstream ss;
            ss << this->title.c_str() << " :: " << this->WinApp.getFPS() << " FPS";
            this->WinApp.setWindowTitle(ss.str());
        }
        this->lastFPS = this->WinApp.getFPS();
    }

    this->InApp.updatePress();

    //FPS brake
    F2C::Timer handletimer;
    do{
        handletimer.reset();
        if(! this->WinApp.getWindowParam(F2C::WindowProperty::Open) ||
            (this->InApp.getPressKey(F2C::KeyboardEvent::Esc) && this->useESC)){  //Window not open or press ESC
                this->Quit();
        }

        //if: time <= FPS && MaxFramerateON
        if(this->WinApp.getTicks()+handletimer.getTime() <= 1.0f/this->framerate && this->MaxFramerateON)
            this->WinApp.Sleep(0.001f); //sleep
    }while(this->WinApp.getTicks()+handletimer.getTime() <= 1.0f/this->framerate && this->MaxFramerateON);

    this->WinApp.startTicks();
}

void GameEngine::Update() {
    this->InApp.update(this->WinApp.getFrame());

	// let the state update the game
	if(!this->states.empty()){
        if(this->states.back())
            states.back()->Update();
	}
}

void GameEngine::Render() {
    this->WinApp.ClearGLScene();  //clear Screen

	// let the state draw the screen
	if(!this->states.empty()){
	    if(this->renderingWholeStack){
	        std::vector<GameState*>::iterator it;
            for(it = this->states.begin();it < this->states.end();it++){
                if(*it){
                    (*it)->Render();
                }
            }
        }else{
            if(this->states.back())
                this->states.back()->Render();
        }
	}

	this->WinApp.UpdateGLScreen();  //Update Screen
}

bool GameEngine::Running(){
    return this->running;
}

void GameEngine::Quit(){
    this->running = false;
}

F2C::Window& GameEngine::getWinApp(){
    return this->WinApp;
}
F2C::Input& GameEngine::getInApp(){
    return this->InApp;
}

namespace Engine{
    GameEngine Game;
    F2C::Input& InApp = Engine::Game.getInApp();
    F2C::Window& WinApp = Engine::Game.getWinApp();
}
