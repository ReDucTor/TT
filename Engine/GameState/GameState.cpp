#include "..\Game.h"
#include "GameState.h"


GameState::GameState(Game* gm)
	:
	pGame(gm),
	pClient(gm->GetClient()),
	MinionPro(L"Minion Pro", 18)
{
}
