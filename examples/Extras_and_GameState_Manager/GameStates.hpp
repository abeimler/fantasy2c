#ifndef GAMESTATES_HPP_INCLUDED
#define GAMESTATES_HPP_INCLUDED

#include "basic.h"

class GameState{
    private:
    friend class GameEngine;
    bool quitScene;

    protected:
	GameState():
        quitScene(false)
    {}

    public:
    virtual ~GameState(){}

	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

	bool isQuitScene(){ return this->quitScene; }
};

class GameEngine{
    private:
    F2C::Window WinApp;
    F2C::Input InApp;
	std::vector<GameState*> states; //states stack
	std::string title;
	F2C::SimpleSprite sprMouse;

	bool running;
	double lastFPS;
	bool fullscreen;

	GameEngine(const GameEngine& copy){}

    public:
    GameEngine();

    bool MaxFramerateON; ///< FPS brake On/Off
    float framerate; ///< FPS rate
    bool useESC; ///< can use ESC to exit program
    bool showFPS; ///< show FPS
    bool renderingWholeStack; ///< rendering whole stack (no Update())
    bool showMouse; ///< show mouse

    ///load mouse graphic
    void loadMouseBitmap(std::string filename);
    void loadMouseBitmap(const F2C::Bitmap* bitmap);

    ///init Window and GameEngine
	void Init(std::string title, F2C::uint width, F2C::uint height, F2C::uint bpp, bool fullscreen);
	void Cleanup(); ///< clear up whole stack (GameState::Clearup())

	void ChangeState(GameState* state); ///< clear up and push a new state
	void PushState(GameState* state); ///< add new state (pls. use new)
	void PopState(); ///< set quitScene(of last state) true
	void UpdateState(); ///< delete all quitScene state

	void HandleEvents(); ///< update Window Handle
	void Update(); ///< call Update() of last state (if quitScene, not update)
	void Render(); ///< call Render() of last state (if quitScene, not render)(if renderingWholeStack: rendering whole stack)

	bool Running(); ///< is running
	void Quit(); ///< quit

	F2C::Window& getWinApp(); ///< get Window
	F2C::Input& getInApp(); ///< get Input

};

namespace Engine{
    extern GameEngine Game;
    extern F2C::Input& InApp; ///< ref to GameEngine::getInApp()
    extern F2C::Window& WinApp; ///< ref to GameEngine::getWinApp()
}

#endif // GAMESTATES_HPP_INCLUDED
