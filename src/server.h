#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "Connection.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


class Server
{
private:

    Connection m_connection;

    WSADATA     m_wsaData;
    int         m_iResult;

    SOCKET      m_ListenSocket = INVALID_SOCKET;
    SOCKET      m_ClientSocket = INVALID_SOCKET;

    struct addrinfo* m_result = NULL;
    struct addrinfo m_hints;

    //int         m_iSendResult;
    //char        m_recvbuf[DEFAULT_BUFLEN];
    //int         m_recvbuflen = DEFAULT_BUFLEN;
public:


    Server();       // Constructeur
    ~Server();      // Destructeur


    void setConnection(Connection newConnection);
	Connection getConnection();


    int RunServer();

    //---
    int initServer();

    int createSocket();
    int bindSocket();
    int closeSocket();

    int listenClient();
    int acceptClient();

    int sendData();
    int receiveData();
};