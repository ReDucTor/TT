#include "Packet.h"
#include <memory>
// NOTE: (reductor) You should avoid using _ prefix as this is reserved for the compiler
// in alot of places.
Packet::Packet(char * _buffer, int _size)
{
	buffer.insert(buffer.end(), _buffer, _buffer + _size);
}

// NOTE: (reductor) This is implicitly defined you should not define it unless your doing
// your own memory management, defining this means that a move constructor is not implicitly
// defined
Packet::Packet(const Packet & p)
{
	buffer = p.buffer;
}


// NOTE: (reductor) This destructor is unnecessary the vector will be released/cleared upon destruction
// so should delete this destructor also.
Packet::~Packet()
{
	buffer.clear();
}

void Packet::Append(char * data, int _size)
{
	buffer.insert(buffer.end(), data, data + _size);
}

void Packet::AppendInt32(int32_t value)
{
	// NOTE: (reductor) Instead of using sizeof(type) you should use sizeof(variable) that way
	// if the type changes the code is still valid, and also allows this body to be identical for
	// the other append functions, reducing room for accidently copy and paste errors.
	Append((char*)&value, sizeof(int32_t));
}

void Packet::AppendInt16(int16_t value)
{
	Append((char*)&value, sizeof(int16_t));
}

// NOTE: (reductor) Append is incorrectly spelt
void Packet::AppednInt8(int8_t value)
{
	Append((char*)&value, sizeof(int8_t));
}
