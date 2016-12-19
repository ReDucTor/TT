#pragma once
#include "../Framework/Graphics.h"
#include "../Framework/AnimatedSurface.h"
#include "..\UI\GUIManager.h"

class Game;
class Client;

class GameState {
public:
	GameState(Game* gm);
	virtual void Draw(Graphics & gfx){}
	virtual void Update(){}
	virtual void GlobalButtonHandler();
protected:
	TextSurface::Font MinionPro;
	//Pointers
	Game* pGame;
	Client* pClient;
	GUIManager* pGUI;
};