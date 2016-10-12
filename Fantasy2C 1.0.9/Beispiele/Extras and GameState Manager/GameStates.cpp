#include "GameStates.hpp"

GameEngine* GameEngine::instance = NULL;

GameEngine* GameEngine::getInstance(){
    if(!GameEngine::instance)
        GameEngine::instance = new GameEngine;
    return GameEngine::instance;
}

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

	F2C::Input::getInstance()->InitInput();  //init Input

    F2C::Window::getInstance()->setWindowHint(F2C::WindowProperty::NoResize,true);  //set Option:Window No Resize = true
    F2C::Window::getInstance()->CreateGLWindow(this->title.c_str(),width,height,bpp,fullscreen);  //create Window
    F2C::Window::getInstance()->setWindowPosition(160,120);

    F2C::Window::getInstance()->InitGL();
    F2C::LogError::ClearLog();

	F2C::WinApp.startTicks();
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
	F2C::Window::getInstance()->ShutdownGLWindow();
}

void GameEngine::ChangeState(GameState* state) {
	// cleanup the current state
	if ( !this->states.empty() ) {
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
    //FPS brake
	if(this->MaxFramerateON){
	    F2C::Timer handletimer;
        do{
            handletimer.reset();
            F2C::Input::getInstance()->update();
            if(! F2C::Window::getInstance()->getWindowParam(F2C::WindowProperty::Open) ||
                (F2C::Input::getInstance()->getPressKey(F2C::KeyboardEvent::Esc) && this->useESC)){  //Window not open or press ESC
                    this->Quit();
            }

            //if: time <= FPS && MaxFramerateON
            if(F2C::Window::getInstance()->getTicks()+handletimer.getTime() <= 1.0f/this->framerate && this->MaxFramerateON)
                F2C::Window::getInstance()->Sleep(0.001f); //sleep
        }while(F2C::Window::getInstance()->getTicks()+handletimer.getTime() <= 1.0f/this->framerate && this->MaxFramerateON);
    }

    F2C::Window::getInstance()->startTicks();

    if(this->showFPS){
        if(this->lastFPS != F2C::Window::getInstance()->getFPS()){
            std::stringstream ss;
            ss << this->title.c_str() << " :: " << F2C::Window::getInstance()->getFPS() << " FPS";
            F2C::Window::getInstance()->setWindowTitle(ss.str());

            this->lastFPS = F2C::Window::getInstance()->getFPS();
        }
    }
}

void GameEngine::Update() {
    F2C::InKeyApp.update();

	// let the state update the game
	if(!this->states.empty()){
        if(this->states.back())
            states.back()->Update();
	}
}

void GameEngine::Render() {
    F2C::WinApp.ClearGLScene();  //clear Screen

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

	F2C::Window::getInstance()->UpdateGLScreen();  //Update Screen
}

bool GameEngine::Running(){
    return this->running;
}

void GameEngine::Quit(){
    this->running = false;
}


