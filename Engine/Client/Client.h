#pragma once
#define NOMINMAX
#ifndef _INC_WINDOWS
#include "..\Framework\ChiliWin.h"
#endif
// NOTE: (reductor) These headers are unused
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
	// NOTE: (reductor) Should be using RAII to close this socket
	SOCKET Connection;
	// NOTE: (reductor) addr is unclear it could be Clients address or Servers address
	SOCKADDR_IN addr;
	// NOTE: (reductor) addrLen is only used as a const value on connect, should just use sizeof(addr) on connect()
	int addrLen = sizeof(addr);
	PacketManager pm;
	GameState* pGameState;
};

// NOTE: (reductor) You should avoid singletons, and 'static' within this context for this variable means that it's file local
// and within a header file this means that 'pClient' is an entirely new variable for every .cpp file that includes Client.h
// you should _never_ use 'static' for a global variable within a header file. It's only usage that is currently 'necessary' is
// within 'UserMsgHandler' which should be created using std::thread and pass in the Client as an argument to UserMsgHandler.
// (See similar comment on Pindrought's tutorials)
static Client * pClient;