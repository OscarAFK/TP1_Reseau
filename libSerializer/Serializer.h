#pragma once
#include <vector>
#include <iostream>
#include "Compressor.h"

class Serializer 
{
public:
	Serializer();
	Serializer(int size);
	~Serializer() = default;

	template <typename T, std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<T>>>* = nullptr>
	void Serialize(T& val) {
		unsigned amount = sizeof(val)/sizeof(char);
		
		unsigned newSize = m_container.size() + amount;
		
		m_container.resize(newSize);

		memcpy(m_container.data() + m_posContainer, &val, amount);
		m_posContainer += amount;

	}

	void Serialize(char* charArray, int sizeOfArray);

	//getter
	std::vector<char>* getContainer();

private:

	std::vector<char> m_container;
	int m_posContainer;
};
