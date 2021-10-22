#include "Serializer.h"

Serializer::Serializer() : m_posContainer(0)
{
}

Serializer::Serializer(int size) : m_posContainer(0)
{
	m_container = std::vector<char>(size);
}

void Serializer::Serialize(char* charArray, int sizeOfArray)
{
	unsigned sizeOfArrayB = sizeOfArray * (sizeof(charArray) / sizeof(char*));

	m_container.resize(m_container.size() + sizeOfArrayB);

	memcpy(m_container.data() + m_posContainer, charArray, sizeOfArrayB * sizeof(char*));
	m_posContainer += sizeOfArrayB;
}

std::vector<char>* Serializer::getContainer()
{
	return &m_container;
}
