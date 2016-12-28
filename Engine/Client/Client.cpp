#include "Client.h"
#include "..\Game.h"

Client::Client()
{
	//WinSock Startup
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		MessageBoxA(NULL, "WinSock failed to startup", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	addr.sin_port = htons(5555);
	addr.sin_family = AF_INET;
	pClient = this;
	pGameState = nullptr;
}

bool Client::Connect()
{
	Connection = socket(addr.sin_family, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, addrLen) != 0) {
		MessageBoxA(NULL, "Failed to connect", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)UserMsgHandler, NULL, NULL, NULL);
	return true;
}

bool Client::CloseConnection()
{
	if (closesocket(Connection) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAENOTSOCK) {
			return true;
		}
		std::string errormsg = "Failed close socket. Error: " + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, errormsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	pm.Clear();
	return true;
}

int Client::UserMsgHandler()
{
	PacketType ptype;
	while (true) {
		if (!pClient->GetPacketType(ptype)) {
			break;
		}
		if (!pClient->pGameState->PacketHandler(ptype)) {
			break;
		}
	}
	std::cout << "Lost Connection to the server" << std::endl;
	if (!pClient->CloseConnection()) {
		std::cout << "Failed to close socket" << std::endl;
	}
	else {
		std::cout << "Socket was closed" << std::endl;
	}
	return 0;
}

void Client::PacketSenderThread()
{
	while(pClient->pm.HavePackets()) {
		Packet p = pClient->pm.Retrieve();
		if (!pClient->SendAllBytes((char*)&p.buffer.front(), (int)p.buffer.size())) {
			std::cout << "failed to send packet" << std::endl;
		}
	}
}

void Client::SetGameState(GameState * state)
{
	pGameState = state;
}
