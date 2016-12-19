#pragma once
#include "GameStateFirstPhase.h"

class GameStateLogin :public GameStateFirstPhase {
public:
	GameStateLogin(Game* gm);
	void Draw(Graphics& gfx);
	void Update();
	void ButtonHandler();
private:
	Surface UILoginPanel;
};