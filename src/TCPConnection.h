#pragma once
#include "Connection.h"

class TCPConnection : public Connection {
public:
	TCPConnection(std::string addr, std::string port);
	TCPConnection(int socket);
	~TCPConnection() = default;

	void sendMessage(const std::string message);
	int receiveMessage(char* recvbuf);
};

