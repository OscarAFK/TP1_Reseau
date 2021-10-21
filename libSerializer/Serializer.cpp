#include "Serializer.h"

Serializer::Serializer() : m_posContainer(0)
{
}

Serializer::Serializer(int size) : m_posContainer(0)
{
	m_container = std::vector<char>(size);
}

const std::vector<char> Serializer::getContainer()
{
	return m_container;
}
