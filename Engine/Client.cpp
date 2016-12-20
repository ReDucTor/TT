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

bool Client::ProcessPacket(PacketType packettype)
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
	PacketType ptype;
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

bool Client::SendAllBytes(char * data, int totalbytes)
{
	int bytessent = 0;
	while (bytessent < totalbytes) {
		int ReturnCheck = send(Connection, data - bytessent, totalbytes - bytessent, NULL);
		if (ReturnCheck = SOCKET_ERROR) {
			return false;
		}
		bytessent += ReturnCheck;
	}
	return true;
}

bool Client::RecvAllBytes(char * data, int totalbytes)
{
	int bytesreceived = 0;
	while (bytesreceived < totalbytes) {
		int ReturnCheck = recv(Connection, data - bytesreceived, totalbytes - bytesreceived, NULL);
		if (ReturnCheck == SOCKET_ERROR) {
			return false;
		}
		bytesreceived += ReturnCheck;
	}
	return true;
}

bool Client::SendInt32(int32_t int32) {
	int32 = htonl(int32);
	if (!SendAllBytes((char*)&int32,sizeof(int32))){
		return false;
	}
	return true;
}

bool Client::GetInt32(int32_t& int32) {
	if (!RecvAllBytes((char*)&int32,sizeof(int32))) {
		int32 = ntohl(int32);
		return false;
	}
	return true;
}

bool Client::SendPacketType(PacketType type) {
	if (!SendInt32(type)) {
		return false;
	}
	return true;
}

bool Client::GetPacketType(PacketType & type) {
	int32_t packettype;
	if (!GetInt32(packettype)) {
		return false;
	}
	type = (PacketType)packettype;
	return true;
}

bool Client::SendMsg(std::string msg, bool incPacketType) {
	if (incPacketType) {
		if (!SendPacketType(ChatMessage)) {
			return false;
		}
	}
	int32_t msglen = (int32_t)msg.size();
	if (!SendInt32(msglen)) {
		return false;
	}
	if (!SendAllBytes((char*)&msg,msglen)) {
		return false;
	}
	return true;
}

bool Client::GetMsg(std::string & msg) {
	int32_t msglen;
	if (!GetInt32(msglen)) {
		return false;
	}
	char * _msg = new char[msglen + 1];
	_msg[msglen] = '\0';
	if (!RecvAllBytes(_msg, msglen)) {
		delete[] _msg;
		return false;
	}
	msg = _msg;
	delete[] _msg;
	return true;
}

