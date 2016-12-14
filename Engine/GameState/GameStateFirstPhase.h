#pragma once
#include "GameState.h"

class GameStateFirstPhase :public GameState {
public:
	GameStateFirstPhase(Game* gm);
	virtual void Draw(Graphics& gfx);
protected:
	Surface logoimg;
	Surface backgroundimg;
};