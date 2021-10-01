#include "server.h"

int Server::initServer()
{
    /*
    // Initialize Winsock
    m_iResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
    if (m_iResult != 0) {
        printf("WSAStartup failed with error: %d\n", m_iResult);
        return 1;
    }

    ZeroMemory(&m_hints, sizeof(m_hints));
    m_hints.ai_family = AF_INET;
    m_hints.ai_socktype = SOCK_STREAM;
    m_hints.ai_protocol = IPPROTO_TCP;
    m_hints.ai_flags = AI_PASSIVE;

    // Resolve the Server address and port
    m_iResult = getaddrinfo(NULL, DEFAULT_PORT, &m_hints, &m_result);
    if (m_iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", m_iResult);
        WSACleanup();
        return 1;
    }
    return 0;*/
}

int Server::createSocket()
{
    // Create a SOCKET for connecting to Server
    m_ListenSocket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
    if (m_ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(m_result);
        WSACleanup();
        return 1;
    }
    return 0;
}

int Server::bindSocket()
{
    // Setup the TCP listening socket
    m_iResult = bind(m_ListenSocket, m_result->ai_addr, (int)m_result->ai_addrlen);
    if (m_iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(m_result);
        closesocket(m_ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(m_result);
    return 0;
}

int Server::closeSocket()
{
    return 0;

    // shutdown the connection since we're done
    m_iResult = shutdown(m_ClientSocket, SD_SEND);
    if (m_iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(m_ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(m_ClientSocket);
    WSACleanup();

}

int Server::listenClient()
{
    m_iResult = listen(m_ListenSocket, SOMAXCONN);
    if (m_iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(m_ListenSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int Server::acceptClient()
{
    // Accept a client socket
    m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
    if (m_ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(m_ListenSocket);
        WSACleanup();
        return 1;
    }
    // No longer need Server socket
    closesocket(m_ListenSocket);
    return 0;
}

int Server::sendData()
{
    m_iSendResult = send(m_ClientSocket, m_recvbuf, m_iResult, 0);
    if (m_iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(m_ClientSocket);
        WSACleanup();
        return 1;
    }
    printf("Bytes sent: %d\n", m_iSendResult);
    return 0;
}

int Server::receiveData()
{
    /*
    m_iResult = recv(m_ClientSocket, m_recvbuf, m_recvbuflen, 0);
    if (m_iResult > 0) {
        printf("Bytes received: %d\n", m_iResult);

    }
    else if (m_iResult == 0)
        printf("Connection closing...\n");
    else {
        printf("recv failed with error: %d\n", WSAGetLastError());
        closesocket(m_ClientSocket);
        WSACleanup();
        return 1;
    }
    return 0;*/
}
