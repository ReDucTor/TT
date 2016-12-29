#include "..\Game.h"
#include "GameStateStartUp.h"
#include "GameStateSelectServer.h"

GameStateStartUp::GameStateStartUp(Game* gm)
	:
	GameStateFirstPhase(gm),
	LoadIco("..\\data\\textures\\LoadSheetIcon\\load", 13, 3)
{
	//Disable couple buttons that are created on parent class 
	pGUI->GetElement("SETTINGS")->Disable();
	pGUI->GetElement("QUITGAME")->Disable();
	LoadPhase = Loading;
}

void GameStateStartUp::Update()
{
	LoadIco.Update();
	switch (LoadPhase)
	{
	case Loading:// load some kind a resource if needed
		Log("Startup:Resources Loaded");
		LoadPhase = Connecting;
		break;
	case FailedToLoadRess:
		LogErr("Startup:Failed to laod Resources");
		break;
	case Connecting:// establish connection to server
		if (pClient->Connect()) {
			LoadPhase = RetrieveData;
		}
		else {
			LogErr("Startup:Failed to connect");
		}
		break;
	case RetrieveData://send request to server for gameInfo(serverlist , and version)
	{
		Packet p;
		p.AppendInt16(Client::PacketType::General_RequestGameInfo);
		pClient->GetPM()->Append(p);
		LoadPhase = WaitingForData;
		break;
	}
	case VersionCheck://Check if server and client versions mach
	{
		char ver[10];
		GetPrivateProfileStringA("VERSION", "Version", "NONE", ver, 10, "..\\data\\version.ini");
		if (serverVersion == ver) {
			LoadPhase = Connected;
		}
		else {
			// pop up wrong version and exit
		}
		break;
	}
	case Connected:// procced to next game state
		Log("Startup: Connected");
		pGUI->ClearGUI();
		pGame->SetGameState(std::make_unique<GameStateSelectServer>(pGame,Serverlist));
		break;
	}
}

bool GameStateStartUp::PacketHandler(Client::PacketType type)
{
	switch (type)
	{
		case Client::PacketType::General_RequestGameInfo://retrieve server version and server list (db,name)
		{
			// NOTE: (reductor) Given a platform where 'int' is not int32_t you might get a compile
			// error with Get32Bits
			int listcount;
			if (!pClient->GetMsg(serverVersion))
				return false;
			if (!pClient->Get32Bits(listcount))
				return false;

			for (int i = 0; i < listcount; i++) {
				std::string db;
				std::string name;
				if (!pClient->GetMsg(db))
					return false;
				if (!pClient->GetMsg(name))
					return false;
				Serverlist.emplace_back(db, name);
			}
			// NOTE: (reductor) This is a race condition with different threads reading and writing 
			// 'LoadPhase' and 'Serverlist' variables, while you might assign them in this specific
			// order, there is no guarantee's that they will be set in that exact order from the
			// view of different threads. (Which is why you normally use locks or atomics)
			LoadPhase = VersionCheck;
			break;
		}
	}
	return true;
}

void GameStateStartUp::Draw(Graphics & gfx)
{
	GameStateFirstPhase::Draw(gfx);
	LoadIco.DrawAlfa(560, 520, gfx);
	switch (LoadPhase)
	{
		case Loading:
			gfx.DrawText("Loading...", { 643, 550 }, MinionPro, {35,35,35});
			break;
		case Connecting:
		case RetrieveData:
		case WaitingForData:
		case VersionCheck:
			gfx.DrawText("Connecting...", { 643, 550 }, MinionPro, { 35,35,35 });
			break;
		case Connected:
			gfx.DrawText("Connected", { 643, 550 }, MinionPro, { 35,35,35 });
			break;
	}
}

