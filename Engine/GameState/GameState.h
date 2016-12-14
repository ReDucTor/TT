#pragma once
#include "../Framework/Graphics.h"
#include "../Framework/AnimatedSurface.h"

class Game;
class Client;
class GameState {
public:
	GameState(Game* gm);
	virtual void Draw(Graphics & gfx){}
	virtual void Update(){}
protected:
	TextSurface::Font MinionPro;
	//Pointers
	Game* pGame;
	Client* pClient;
};