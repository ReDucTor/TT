#include "GameStateLogin.h"
#include "..\UI\GUITextInput.h"
GameStateLogin::GameStateLogin(Game * gm)
	:
	GameStateFirstPhase(gm),
	UILoginPanel(Surface::FromFile("..\\data\\textures\\UI\\Menus\\LoginInput.png"))
{
	pGUI->AddTextInput("username", 589, 313, 185, 25);
	pGUI->AddTextInput("password", 589, 361, 185, 25);
	pGUI->AddButton("login", "LOG IN", "..\\data\\textures\\UI\\buttons\\login", 616, 405, 134, 29, L"MinionPro", 18, false);
	auto username = std::static_pointer_cast<GUITextInput>(pGUI->GetElement("username"));
	auto password = std::static_pointer_cast<GUITextInput>(pGUI->GetElement("password"));
	password->SetTypePassword(true);
}

void GameStateLogin::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
	UILoginPanel.DrawAlfa(587, 311, gfx);
}

void GameStateLogin::Update()
{
}
