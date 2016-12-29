#include "..\Game.h"
#include "GameState.h"


// NOTE: (reductor) You should stop using pointers for something that is required, and use
// a reference instead
GameState::GameState(Game* gm)
	:
	// NOTE: (reductor) You should try to keep the initializer list in the order in which
	// variables are defined in the header file, as this is the actual order they are
	// initialized, and not the order you define here.
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
