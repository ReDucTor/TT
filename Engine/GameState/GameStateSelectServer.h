#pragma once
#include "GameStateFirstPhase.h"
#include "..\Framework\Surface.h"

class GameStateSelectServer:public GameStateFirstPhase {
public:
	GameStateSelectServer(Game* gm);
	virtual void Draw(Graphics& gfx);
	virtual void Update();
private:
	Surface UIPanel;
};