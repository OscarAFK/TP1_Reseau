#pragma once
#include "Connection.h"

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

// permet au serveur de créer une connexion lorsqu’il reçoit une
// demande de connexion d’un client.
class Terminal : public Network {

private:

	//int m_ListenSocket = NULL;
	int m_iResult;

public :

	//Terminal(int listenSocket);
	Terminal(char * addr, char * port);
	Terminal() = default;
	~Terminal() = default;

	int Connect();
};