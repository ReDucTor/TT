#pragma once
#include "GameStateFirstPhase.h"
#include "..\DataStruct\ServerInfo.h"
class GameStateStartUp :public GameStateFirstPhase {
private:
	enum LoadStatus {
		Loading,
		Connecting,
		Connected,
		RetrieveData,
		WaitingForData,
		FailedToConnect,
		FailedToLoadRess,
		VersionCheck
	};
public:
	GameStateStartUp(Game* gm);
	void Draw(Graphics &gfx)override;
	void Update()override;
	bool PacketHandler(Client::PacketType type)override;
private:
	LoadStatus LoadPhase;
	AnimatedSurface LoadIco;
	std::vector<ServerInfo> Serverlist;
	std::string serverVersion;
};

