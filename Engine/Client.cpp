#include "Client.h"

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
	return true;
}

bool Client::ProcessPacket(Packet packettype)
{
	switch (packettype)
	{
		case ChatMessage:
		{
			std::string msg;
			if (!GetMsg(msg)) {
				return false;
			}
			std::cout << msg << std::endl;
			break;
		}
		case LoginSuccessful:
			break;
		case WrongPassword:
			break;
		case NoSuchUser:
			break;
		default:
			std::cout << "Unknown packet: " << packettype << std::endl;
			break;
	}
	return true;
}

int Client::UserMsgHandler()
{
	Packet ptype;
	while (true) {
		if (!pClient->GetPacketType(ptype)) {
			break;
		}
		if (!pClient->ProcessPacket(ptype)) {
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

bool Client::SendInt(int _int) {
	int ReturnCheck = send(Connection, (char*)& _int, sizeof(int), NULL);
	if (ReturnCheck == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool Client::GetInt(int& _int) {
	int ReturnCheck = recv(Connection, (char*)& _int, sizeof(int), NULL);
	if (ReturnCheck == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool Client::SendPacketType(Packet type) {
	int ReturnCheck = send(Connection, (char*)& type, sizeof(Packet), NULL);
	if (ReturnCheck == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool Client::GetPacketType(Packet & type) {
	int ReturnCheck = recv(Connection, (char*)& type, sizeof(Packet), NULL);
	if (ReturnCheck == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool Client::SendMsg(std::string msg) {
	if (!SendPacketType(ChatMessage)) {
		return false;
	}
	int msglen = static_cast<int>(msg.size());
	if (!SendInt(msglen)) {
		return false;
	}
	int ReturnCheck = send(Connection, msg.c_str(), msglen, NULL);
	if (ReturnCheck == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool Client::GetMsg(std::string & msg) {
	int msglen;
	if (!GetInt(msglen)) {
		return false;
	}
	char * _msg = new char[msglen + 1];
	_msg[msglen] = '\0';
	int ReturnCheck = recv(Connection, _msg, msglen, NULL);
	msg = _msg;
	delete[] _msg;
	if (ReturnCheck == SOCKET_ERROR) {
		return false;
	}
	return true;
}

