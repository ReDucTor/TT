#pragma once
#include "GameStateFirstPhase.h"

class GameStateLogin :public GameStateFirstPhase {
public:
	GameStateLogin(Game* gm);
	virtual void Draw(Graphics& gfx);
	virtual void Update();
};