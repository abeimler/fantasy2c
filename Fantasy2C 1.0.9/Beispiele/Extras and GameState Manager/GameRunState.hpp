#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "GameStates.hpp"

class GameRunState : public GameState{
    private:
    F2C::SimpleSprite ssprSimple;

    public:
    void Init();
	void Cleanup(){};

	void Update();
	void Render();
};

#endif // GAMESTATE_HPP_INCLUDED
