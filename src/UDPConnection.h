#pragma once
#include "Connection.h"

class UDPConnection : public Connection {
public:
	UDPConnection(std::string addr, std::string port);
	UDPConnection(int socket);
	~UDPConnection() = default;

	void sendMessage(const std::string message);
	int receiveMessage(char* recvbuf);
};