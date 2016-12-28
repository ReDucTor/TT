#pragma once
#include "GameStateFirstPhase.h"
#include "..\Framework\Surface.h"
#include "..\DataStruct\ServerInfo.h"

class GameStateSelectServer:public GameStateFirstPhase {
public:
	GameStateSelectServer(Game* gm,std::vector<ServerInfo> slist);
	void Draw(Graphics& gfx)override;
	void Update()override;
	void ButtonHandler();
private:
	std::vector<ServerInfo> ServerList;
};