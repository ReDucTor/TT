#pragma once
#define NOMINMAX
#ifndef _INC_WINDOWS
#include "..\Framework\ChiliWin.h"
#endif
#include <iostream>
#include <string>
#include "PacketManager.h"

class GameState;

class Client {
public:
	enum PacketType :int16_t{
		Chat_ChatMessage,
		Login_AttemptToLogin,
		Login_WrongPassword,
		Login_NoSuchUser,
		Login_LoginSuccessful,
		General_RequestGameInfo
	};
public:

	Client();
	//Client Handling
	bool Connect();
	bool CloseConnection();
	// General funtions
	PacketManager* GetPM() { return &pm; }
	void PacketSenderThread();
	void SetGameState(GameState* state);
	//buffer handling
	bool Get32Bits(int32_t& int32);
	bool Get16Bits(int16_t& int16);
	bool Get8Bits(int8_t& int8);
	bool GetPacketType(PacketType& type);
	bool GetMsg(std::string & msg);
private:
	bool SendAllBytes(char * data, int totalbytes);
	bool RecvAllBytes(char * data, int totalbytes);
	static int UserMsgHandler();
private:
	SOCKET Connection;
	SOCKADDR_IN addr;
	int addrLen = sizeof(addr);
	PacketManager pm;
	GameState* pGameState;
};

static Client * pClient;