#include "Network.h"
#include <stdio.h>
#include <stdexcept>

Network::Network(char* addr, char* port)
{
    // Initialize Winsock
    WSADATA wsaData;
    m_iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (m_iResult != 0) {
        printf("WSAStartup failed with error: %d \n", m_iResult);
        return;
    }

    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the Server address and port
    if (port == NULL)
        port = DEFAULT_PORT;

    m_iResult = getaddrinfo(addr, port, &hints, &m_result);
    if (m_iResult != 0) {
        printf("getaddrinfo failed with error: %d \n", m_iResult);
        WSACleanup();
        return;
    }
}

Network::Network(int socket)
{
    m_ConnectSocket = socket;
}

Network::~Network()
{
    if (m_ConnectSocket != INVALID_SOCKET) {
        m_iResult = shutdown(m_ConnectSocket, SD_SEND);
        if (m_iResult == SOCKET_ERROR) {
            printf("Connection: shutdown failed with error: %d\n", WSAGetLastError());
        }
    }
    closesocket(m_ConnectSocket);
    WSACleanup();
}
