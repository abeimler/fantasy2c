#ifndef GAMESTATES_HPP_INCLUDED
#define GAMESTATES_HPP_INCLUDED

#include "basic.h"

class GameState{
    protected:
	GameState(){}

    public:
    virtual ~GameState(){}

	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
};

class GameEngine{
    private:
	std::vector<GameState*> states; //sates stack
	std::string title;

	bool running;
	double lastFPS;
	bool fullscreen;

	GameEngine(){}
	GameEngine(const GameEngine& copy){}

	static GameEngine* instance;

    public:
    bool MaxFramerateON; //FPS brake On/Off
    float framerate; //FPS rate
    bool useESC; //can use ESC to exit program
    bool showFPS; //show FPS
    bool renderingWholeStack; //rendering whole stack (no Update())

	void Init(std::string title, F2C::uint width, F2C::uint height, F2C::uint bpp, bool fullscreen);
	void Cleanup(); //clear up whole stack (Clearpp())

	void ChangeState(GameState* state); //clear up and push a new state
	void PushState(GameState* state); //add new state (pls. use new)
	void PopState(); //delete last state (used delete)

	void HandleEvents(); //update Window Handle
	void Update(); //call Update() of last state
	void Render(); //call Render() of last state (if renderingWholeStack: rendering whole stack)

	bool Running(); //is running
	void Quit(); //quit

	static GameEngine* getInstance();
};

#endif // GAMESTATES_HPP_INCLUDED
