#include "..\Game.h"
#include "GameStateSelectServer.h"
#include "GameStateLogin.h"

GameStateSelectServer::GameStateSelectServer(Game * gm)
	:
	GameStateFirstPhase(gm),
	UISelectServerPanel(Surface::FromFile("..\\data\\textures\\UI\\Menus\\SelectServer3.png"))
{
}

void GameStateSelectServer::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
	UISelectServerPanel.Draw(592, 280, gfx);
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
