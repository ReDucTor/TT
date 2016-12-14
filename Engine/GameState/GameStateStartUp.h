#pragma once
#include "GameStateFirstPhase.h"

class GameStateStartUp :public GameStateFirstPhase {
private:
	enum LoadStatus {
		LOADING,
		CONNECTING,
		CONNECTED,
		RETRIEVEDATA,
		FAILEDTOCONNECT,
		FAILEDTOLOADRESS
	};
public:
	GameStateStartUp(Game* gm);
	virtual void Draw(Graphics &gfx);
	virtual void Update();
private:
	LoadStatus LoadPhase;
	AnimatedSurface LoadIco;
};

