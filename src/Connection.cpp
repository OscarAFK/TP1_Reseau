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
    //printf("Bytes sent: %d\n", m_iResult);
}

void Connection::receiveMessage(char * recvbuf)
{
    m_iResult = recv(m_ConnectSocket, recvbuf, (int)strlen(recvbuf)+1, 0);
    if (m_iResult > 0)
        //printf("Bytes received: %d\n", m_iResult);
        TRUE;
    else if (m_iResult == 0)
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());
}

void Connection::readMessage()
{
    
}

Connection::Connection(char* addr, char* port) : Network(addr, port)
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
    u_long nonBlocking = 1;
    ioctlsocket(m_ConnectSocket,FIONBIO,&nonBlocking);
}

Connection::Connection(int socket)
{
    m_ConnectSocket = socket;
}

Connection::~Connection()
{
}
