#include "..\Game.h"
#include "GameStateStartUp.h"
#include "GameStateSelectServer.h"

GameStateStartUp::GameStateStartUp(Game* gm)
	:
	GameStateFirstPhase(gm),
	LoadIco("..\\data\\textures\\LoadSheetIcon\\load", 13, 3)
{
	pGUI->GetElement("SETTINGS")->Disable();
	pGUI->GetElement("QUITGAME")->Disable();
	LoadPhase = LOADING;
}

void GameStateStartUp::Update()
{
	LoadIco.Update();
	switch (LoadPhase)
	{
	case LOADING:
		//Log("Startup:Resources Loaded");
		LoadPhase = CONNECTING;
		//LoadPhase = CONNECTED;
		break;
	case FAILEDTOLOADRESS:
		//LogErr("Startup:Failed to laod Resources");
		break;
	case CONNECTING:
		if (pClient->Connect()) {
			LoadPhase = RETRIEVEDATA;
		}
		else {
			LogErr("Startup:Failed to connect");
		}
		break;
	case RETRIEVEDATA:
		
		//Retriev server list from server side
		break;
	case CONNECTED:
		//Log("Startup: Connected");
		pGUI->ClearGUI();
		pGame->SetGameState(std::make_unique<GameStateSelectServer>(pGame));
		break;
	}
}


void GameStateStartUp::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
	LoadIco.DrawAlfa(560, 520, gfx);
	switch (LoadPhase)
	{
		case LOADING:
			gfx.DrawText("Loading...", { 643, 550 }, MinionPro, {35,35,35});
			break;
		case CONNECTING | RETRIEVEDATA:
			gfx.DrawText("Connecting...", { 643, 550 }, MinionPro, { 35,35,35 });
			break;
		case CONNECTED:
			gfx.DrawText("Connected", { 643, 550 }, MinionPro, { 35,35,35 });
			break;
	}
}

