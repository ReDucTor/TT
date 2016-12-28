#pragma once
#include "GameStateFirstPhase.h"

class GameStateLogin :public GameStateFirstPhase {
public:
	GameStateLogin(Game* gm);
	void Draw(Graphics& gfx)override;
	void Update()override;
	void ButtonHandler();
};