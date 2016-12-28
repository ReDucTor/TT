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

bool Client::Get32Bits(int32_t& int32) {
	if (!RecvAllBytes((char*)&int32, sizeof(int32_t))) {
		return false;
	}
	return true;
}

bool Client::Get16Bits(int16_t & int16)
{
	if (!RecvAllBytes((char*)&int16, sizeof(int16_t))) {
		return false;
	}
	return true;
}

bool Client::Get8Bits(int8_t & int8)
{
	if (!RecvAllBytes((char*)&int8, sizeof(int8_t))) {
		return false;
	}
	return true;
}

bool Client::GetPacketType(PacketType & type) {
	int16_t packettype;
	if (!Get16Bits(packettype)) {
		return false;
	}
	type = (PacketType)packettype;
	return true;
}

bool Client::GetMsg(std::string & msg) {
	int32_t msglen;
	if (!Get32Bits(msglen)) {
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
