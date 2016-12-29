#pragma once
#include "../Framework/Graphics.h"
// NOTE: (reductor) This header appears unused
#include "../Framework/AnimatedSurface.h"
// NOTE: (reductor) This can be forward declared
#include "..\UI\GUIManager.h"
#include "..\Client\Client.h"
class Game;

class GameState {
public:
	GameState(Game* gm);
	virtual void Draw(Graphics & gfx){}
	virtual void Update(){}
	// NOTE: (reductor) This is never overwritten should consider making it not virtual
	virtual void GlobalButtonHandler();
	virtual bool PacketHandler(Client::PacketType type) { return false; }
protected:
	TextSurface::Font MinionPro;
	//Pointers
	Game* pGame;
	Client* pClient;
	GUIManager* pGUI;
};