#include "Deserializer.h"

Deserializer::Deserializer()
{
}

Deserializer::Deserializer(char* buffer, int size)
{
	m_buffer = new char[size];
}

Deserializer::~Deserializer()
{
	delete m_buffer;
}

const char* Deserializer::getBuffer() {
	return m_buffer;
}

const int Deserializer::getSize(){
	return m_size;
}
