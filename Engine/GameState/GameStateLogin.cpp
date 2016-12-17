#include "GameStateLogin.h"

GameStateLogin::GameStateLogin(Game * gm)
	:
	GameStateFirstPhase(gm),
	UILoginPanel(Surface::FromFile("..\\data\\textures\\UI\\Menus\\Login2.png"))
{
	pGUI->AddTextInput("LOGIN", 590, 325, 185, 25);
}

void GameStateLogin::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
	UILoginPanel.DrawAlfa(568, 311, gfx);
}

void GameStateLogin::Update()
{
}
