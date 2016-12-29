#include "PacketManager.h"

bool PacketManager::HavePackets()
{
	// NOTE: (reductor) This should lock the mutex, and should use !packets.empty()
	return packets.size() != 0;
}

void PacketManager::Append(Packet p)
{
	std::lock_guard<std::mutex> lock(mtx);
	// NOTE: (reductor) Might be worth doing push(std::move(p)) as this currently results in a copy
	packets.push(p);
}

Packet PacketManager::Retrieve()
{
	std::lock_guard<std::mutex> lock(mtx);
	// NOTE: (reductor) It might be worth using std::move(packets.front()) as this
	// currentl results in a copy
	Packet p = packets.front();
	packets.pop();
	return p;
}

void PacketManager::Clear()
{
	std::lock_guard<std::mutex> lock(mtx);
	// NOTE: (reductor) This swap is unnecessary just do "packets = std::queue<Packet>{}"
	// I added a similar comment for Pindrought's tutorial
	std::queue<Packet> empty;
	std::swap(packets, empty);
}
