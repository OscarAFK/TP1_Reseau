#pragma once

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

class Deserializer {
public:
	Deserializer();
	Deserializer(char* buffer, int size);
	~Deserializer();

	template <typename T>
	void Deserialize(T& val) {
		InputStream stream;
		val.Read(InputStream & stream);
	}

	const char* getBuffer();
	const int getSize();

private:
	char* m_buffer;
	int m_size;
};