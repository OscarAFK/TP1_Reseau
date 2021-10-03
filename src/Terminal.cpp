#include "Terminal.h"
#include "Connection.h"

/*
Terminal::Terminal(int listenSocket) : m_ListenSocket(listenSocket)
{
}*/


Terminal::Terminal(char* addr, char* port) : Network(addr, port)
{
    // Create a SOCKET for connecting to server
    m_ConnectSocket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
    if (m_ConnectSocket == INVALID_SOCKET) {
        printf("InitServer: socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(m_result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    m_iResult = bind(m_ConnectSocket, m_result->ai_addr, (int)m_result->ai_addrlen);
    if (m_iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(m_result);
        closesocket(m_ConnectSocket);
        WSACleanup();
        return;
    }
    freeaddrinfo(m_result);

    m_iResult = listen(m_ConnectSocket, SOMAXCONN);
    if (m_iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(m_ConnectSocket);
        WSACleanup();
        return;
    }
}

int Terminal::Connect()
{
    // Accept a client socket
    int ConnectSocket = accept(m_ConnectSocket, NULL, NULL);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(m_ConnectSocket);
        WSACleanup();
    }
    return ConnectSocket;
}