#pragma once

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


// via elle que nous envoyons et recevons nos messages
class Network {

protected :

	const char* m_sendbuf = "this is a test";

	int m_ConnectSocket = INVALID_SOCKET;
	
	int m_iResult = NULL;
	struct addrinfo* m_result = NULL,
		* m_ptr = NULL;

public:
	int getSocket();

	Network(char * addr, char * port);
	Network(int socket);
	Network()= default;
	~Network();


	
};