#include "..\Game.h"
#include "GameStateSelectServer.h"

GameStateSelectServer::GameStateSelectServer(Game * gm)
	:
	GameStateFirstPhase(gm),
	UIPanel(Surface::FromFile("..\\data\\textures\\SelectServer3.png"))
{
}

void GameStateSelectServer::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
	gfx.DrawSprite(592, 280, UIPanel);
}

void GameStateSelectServer::Update()
{
}
