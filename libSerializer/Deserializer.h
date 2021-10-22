#pragma once
#include <vector>

class Deserializer {
public:
	Deserializer();
	Deserializer(std::vector<char>* buffer, int size);
	~Deserializer();
	
	template <typename T, std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<T>>>* = nullptr>
	T Read() {
		T retValue = *reinterpret_cast<T*>(m_buffer->data() + pos);
		pos += sizeof(retValue) / sizeof(char);
		return retValue;
	}

	std::vector<char> Read(int sizeOfData);

	const std::vector<char>* getBuffer();
	const int getSize();

private:
	std::vector<char> * m_buffer;
	int m_size;
	int pos;
};