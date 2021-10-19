#include "Serializer.h"

Serializer::Serializer()
{
}

Serializer::Serializer(int size) : m_sizeContainer(size)
{
	m_container = new char[size];
}

Serializer::~Serializer()
{
	delete m_container;
}

const char* Serializer::getContainer()
{
	return m_container;
}

const int Serializer::getSizeContainer()
{
	return m_sizeContainer;
}
