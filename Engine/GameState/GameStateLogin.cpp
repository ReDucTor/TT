#include "GameStateLogin.h"
#include "..\UI\GUITextInput.h"
#include "..\UI\GUIButton.h"

GameStateLogin::GameStateLogin(Game * gm)
	:
	GameStateFirstPhase(gm)
{
	pGUI->AddPanel("loginpanel", "..\\data\\textures\\UI\\Menus\\LoginInput.png", 587, 311);
	pGUI->AddTextInput("username", 589, 313, 185, 25);
	pGUI->AddTextInput("password", 589, 361, 185, 25);
	pGUI->AddButton("loginbtn", "", "..\\data\\textures\\UI\\buttons\\login", 616, 405);
	auto username = std::static_pointer_cast<GUITextInput>(pGUI->GetElement("username"));
	auto password = std::static_pointer_cast<GUITextInput>(pGUI->GetElement("password"));
	password->SetTypePassword(true);
}

void GameStateLogin::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
}

void GameStateLogin::Update()
{
	ButtonHandler();
}

void GameStateLogin::ButtonHandler()
{
	GlobalButtonHandler();//handles global button with are initialized on GameState class
	if (pGUI->GetElement("loginbtn")->IsLMB()) {
		//cath data from username and password input and proceed to server side 
	}
}
