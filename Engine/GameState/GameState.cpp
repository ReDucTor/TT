#include "..\Game.h"
#include "GameState.h"


GameState::GameState(Game* gm)
	:
	pGame(gm),
	pClient(gm->GetClient()),
	MinionPro(L"Minion Pro", 18),
	pGUI(gm->GetGUI())
{
	gm->GetGUI()->AddButton("SETTINGS", "", "..\\data\\textures\\UI\\buttons\\settings", 1300, 0,L"Arial", 10, false);
	gm->GetGUI()->AddButton("QUITGAME", "", "..\\data\\textures\\UI\\buttons\\exitgame", 1335, 0, L"Arial", 10, false);
}

void GameState::GlobalButtonHandler()
{
	if (pGUI->GetElement("SETTINGS")->IsLMB()) {
		//enable settings pannel that is already created just disabled
	}

	if (pGUI->GetElement("QUITGAME")->IsLMB()) {
		//enable confirmation panel to quit game 
	}
}
