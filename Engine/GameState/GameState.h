#pragma once
#include "../Framework/Graphics.h"
#include "../Framework/AnimatedSurface.h"
#include "..\UI\GUIManager.h"
#include "..\Client\Client.h"
class Game;

class GameState {
public:
	GameState(Game* gm);
	virtual void Draw(Graphics & gfx){}
	virtual void Update(){}
	virtual void GlobalButtonHandler();
	virtual bool PacketHandler(Client::PacketType type) { return false; }
protected:
	TextSurface::Font MinionPro;
	//Pointers
	Game* pGame;
	Client* pClient;
	GUIManager* pGUI;
};