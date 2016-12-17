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
	pGame->SetGameState(std::make_unique<GameStateLogin>(pGame));
}
