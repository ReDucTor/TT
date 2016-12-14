#include "..\Game.h"
#include "GameStateFirstPhase.h"

GameStateFirstPhase::GameStateFirstPhase(Game* gm)
	:
	GameState(gm),
	logoimg(Surface::FromFile("..\\data\\textures\\logo.png")),
	backgroundimg(Surface::FromFile("..\\data\\textures\\bg.png"))
{
}

void GameStateFirstPhase::Draw(Graphics & gfx)
{
	gfx.DrawSprite(0, 0, backgroundimg);
	gfx.DrawSpriteAlfa(527, 100, logoimg);
}
