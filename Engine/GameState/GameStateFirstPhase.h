#pragma once
#include "GameState.h"

class GameStateFirstPhase :public GameState {
public:
	GameStateFirstPhase(Game* gm);
	virtual void Draw(Graphics& gfx) override;
protected:
	Surface logoimg;
	Surface backgroundimg;
};