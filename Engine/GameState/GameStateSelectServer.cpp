#include "..\Game.h"
#include "GameStateSelectServer.h"
#include "GameStateLogin.h"

GameStateSelectServer::GameStateSelectServer(Game * gm, std::vector<ServerInfo> slist)
	:
	GameStateFirstPhase(gm),
	ServerList(slist)
{
	pGUI->AddPanel("selectserverpanel", "..\\data\\textures\\UI\\Menus\\selectserver.png", 592, 280);
}

void GameStateSelectServer::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
}

void GameStateSelectServer::Update()
{
	pGUI->ClearGUI();
	pGame->SetGameState(std::make_unique<GameStateLogin>(pGame));
}

void GameStateSelectServer::ButtonHandler()
{
	GlobalButtonHandler();//handles global button with are initialized on GameState class
	//handle local buttons with are unique for this state
}
