#pragma once

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


// via elle que nous envoyons et recevons nos messages
class Network {

protected :

	int m_ConnectSocket = INVALID_SOCKET;
	
	int m_iResult = NULL;
	struct addrinfo* m_result = NULL,
		* m_ptr = NULL;

public:

	bool verbose;

	int getSocket();
	std::string getName();

	virtual void Update();
	Network(std::string addr, std::string port);
	Network(int socket);
	Network()= default;
	~Network();


	
};