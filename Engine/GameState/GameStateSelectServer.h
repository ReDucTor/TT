#pragma once
#include "GameStateFirstPhase.h"
#include "..\Framework\Surface.h"

class GameStateSelectServer:public GameStateFirstPhase {
public:
	GameStateSelectServer(Game* gm);
	void Draw(Graphics& gfx);
	void Update();
	void ButtonHandler();
private:
	Surface UISelectServerPanel;
};