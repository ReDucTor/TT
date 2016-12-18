#include "GameStateLogin.h"
#include "..\UI\GUITextInput.h"
GameStateLogin::GameStateLogin(Game * gm)
	:
	GameStateFirstPhase(gm),
	UILoginPanel(Surface::FromFile("..\\data\\textures\\UI\\Menus\\Login2.png"))
{
	pGUI->AddTextInput("username", 590, 325, 185, 25);
	pGUI->AddTextInput("password", 590, 373, 185, 25);
	auto username = std::static_pointer_cast<GUITextInput>(pGUI->GetElement("username"));
	auto password = std::static_pointer_cast<GUITextInput>(pGUI->GetElement("password"));
	password->SetTypePassword(true);
}

void GameStateLogin::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
	UILoginPanel.DrawAlfa(568, 311, gfx);
}

void GameStateLogin::Update()
{
}
