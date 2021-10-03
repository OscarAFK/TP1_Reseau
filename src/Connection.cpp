#include "Connection.h"
#include <stdio.h>
#include <stdexcept>

void Connection::sendMessage(char * message)
{
    m_iResult = send(m_ConnectSocket, message, (int)strlen(message)+1, 0);
    if (m_iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        WSACleanup();
    }
    printf("Bytes sent: %d\n", m_iResult);
}

void Connection::receiveMessage(char * recvbuf)
{
    //int		m_recvbuflen = DEFAULT_BUFLEN;
    //char	m_recvbuf[DEFAULT_BUFLEN];
    m_iResult = recv(m_ConnectSocket, recvbuf, (int)strlen(recvbuf)+1, 0);
    if (m_iResult > 0)
        printf("Bytes received: %d\n", m_iResult);
    else if (m_iResult == 0)
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());
}

void Connection::ConnectToServer()
{
    // Attempt to connect to an address until one succeeds
    for (m_ptr = m_result; m_ptr != NULL; m_ptr = m_ptr->ai_next) {

        //Create a SOCKET for connecting to the server
        m_ConnectSocket = socket(m_ptr->ai_family, m_ptr->ai_socktype,
            m_ptr->ai_protocol);
        if (m_ConnectSocket == INVALID_SOCKET) {
            printf("ConnectionToServer: socket failed with error: %d \n", m_iResult);
            WSACleanup();
            return;
        }

        // Connect to server.
        m_iResult = connect(m_ConnectSocket, m_ptr->ai_addr, (int)m_ptr->ai_addrlen);
        if (m_iResult == SOCKET_ERROR) {
            closesocket(m_ConnectSocket);
            m_ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
}

void Connection::InitServer()
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

int Connection::getSocket()
{
    return m_ConnectSocket;
}

Connection::Connection(char* addr, char* port)
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

Connection::Connection(int socket)
{
    m_ConnectSocket = socket;
}

Connection::~Connection()
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
