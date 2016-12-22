#pragma once
#define NOMINMAX
#ifndef _INC_WINDOWS
#include "..\Framework\ChiliWin.h"
#endif
#include <iostream>
#include <string>


class Client {
private:
	enum PacketType{
		ChatMessage,
		AttemptToLogin,
		WrongPassword,
		NoSuchUser,
		LoginSuccessful,
		RequestServerInfo
	};
public:
	Client();
	bool Connect();
	bool CloseConnection();
	bool SendMsg(std::string msg, bool incPacketType = true);
private:
	bool SendAllBytes(char * data, int totalbytes);
	bool RecvAllBytes(char * data, int totalbytes);
	bool ProcessPacket(PacketType packettype);
	static int UserMsgHandler();
	bool SendInt32(int32_t int32);
	bool GetInt32(int32_t& int32);
	bool SendPacketType(PacketType type);
	bool GetPacketType(PacketType& type);
	bool GetMsg(std::string & msg);
private:
	SOCKET Connection;
	SOCKADDR_IN addr;
	int addrLen = sizeof(addr);
};

static Client * pClient;