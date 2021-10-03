#pragma once
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "Connection.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class Client {
	public:

		Client() = default;		// constructeur
		Client(char * addr, char * port);		// constructeur
		~Client();		// destructeur

		int Update();
		void readSocket();
		void sendMessage(char* message);
		



	private:

		Connection* m_connection;
};