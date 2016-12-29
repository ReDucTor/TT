#include "Client.h"

// NOTE: (reductor) You should avoid splitting the methods of one object over different files
// it results in information scatter and makes it harder to reason about its operations
bool Client::SendAllBytes(char * data, int totalbytes)
{
	int bytessent = 0;
	while (bytessent < totalbytes) {
		// NOTE: (reductor) This should be data + bytessent
		// NOTE: (reductor) You should not use NULL for 'flags' use 0 instead
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
		// NOTE: (reductor) Should be data + bytesreceived
		// NOTE: (reductor) You should not use NULL for 'flags' use 0 instead
		int ReturnCheck = recv(Connection, data - bytesreceived, totalbytes - bytesreceived, NULL);
		// NOTE: recv(..) of 0 is saying the other end gracefully disconnected, so should handle that
		// otherwise the next recv() will fail.
		if (ReturnCheck == SOCKET_ERROR) {
			return false;
		}
		bytesreceived += ReturnCheck;
	}
	return true;
}

bool Client::Get32Bits(int32_t& int32) {
	// NOTE: (reductor) Should also use sizeof(variable) instead of sizeof(type) as
	// this is safer for future copy and paste and works better if the code changes.
	// NOTE: (reductor) Instead of this if() you can just use "return RecvAllBytes(...);"
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
	// NOTE: (reductor) Instead of using a new buffer here you can resize 'msg' and store into it:
	// msg.resize(msgLen)
	// return RecvAllBytes(&msg[0], msgLen);
	char * _msg = new char[msglen + 1];
	_msg[msglen] = '\0';
	if (!RecvAllBytes(_msg, msglen)) {
		delete[] _msg;
		return false;
	}
	// NOTE: (reductor) This will not work well 'msg' contains any \0 bytes, storing straight into std::string will
	msg = _msg;
	delete[] _msg;
	return true;
}
