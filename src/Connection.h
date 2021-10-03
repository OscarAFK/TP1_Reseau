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

#include "Network.h"

// via elle que nous envoyons et recevons nos messages
class Connection : public Network {

public:
	void sendMessage(char * message);
	int receiveMessage(char * recvbuf);
	void readMessage();

	Connection(char * addr, char * port);
	Connection(int socket);
	Connection()= default;
	~Connection();


	
};