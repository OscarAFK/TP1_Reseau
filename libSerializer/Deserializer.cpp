#include "Deserializer.h"

Deserializer::Deserializer()
{
}

Deserializer::Deserializer(std::vector<char>* buffer, int size) : pos(0), m_size(size)
{
	m_buffer = buffer;
}

Deserializer::~Deserializer()
{
	//delete m_buffer;
}

std::vector<char> Deserializer::Read(int sizeOfData)
{
	//char* tmpBuffer;
	//return memcpy(new char[m_size] + pos++, tmpBuffer, m_size * sizeof(T));
	return std::vector<char>(m_buffer->data() + pos, m_buffer->data() + pos + sizeOfData);
}

const std::vector<char>* Deserializer::getBuffer() {
	return m_buffer;
}

const int Deserializer::getSize(){
	return m_size;
}
