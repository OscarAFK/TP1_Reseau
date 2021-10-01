#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
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

		Client();		// constructeur
		~Client();		// destructeur

		void setConnection(Connection newConnection);
		Connection getConnection();

		int runClient();
		//---

		int initialisationWinsock();
		int createSocket();
		int connectServeur();
		//int initBuffer();
		int connexionShutdown();
		int Getaddrinfo(char* addr);
		



	private:

		Connection m_connection;
		WSADATA m_wsaData;
		SOCKET m_ConnectSocket = INVALID_SOCKET;
		struct addrinfo* m_result = NULL,
			* m_ptr = NULL,
			m_hints;
		//const char* m_sendbuf = "this is a test";
		//char m_recvbuf[DEFAULT_BUFLEN];
		int m_iResult;
		//int m_recvbuflen = DEFAULT_BUFLEN;
};