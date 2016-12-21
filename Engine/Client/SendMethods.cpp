#include "Client.h"

bool Client::SendAllBytes(char * data, int totalbytes)
{
	int bytessent = 0;
	while (bytessent < totalbytes) {
		int ReturnCheck = send(Connection, data - bytessent, totalbytes - bytessent, NULL);
		if (ReturnCheck == SOCKET_ERROR) {
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
	if (!SendAllBytes((char*)&int32, sizeof(int32))) {
		return false;
	}
	return true;
}

bool Client::GetInt32(int32_t& int32) {
	if (!RecvAllBytes((char*)&int32, sizeof(int32))) {
		return false;
	}
	int32 = ntohl(int32);
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
	if (!SendAllBytes((char*)msg.c_str(), msglen)) {
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
