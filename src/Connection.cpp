#include "Connection.h"
#include <stdio.h>
#include <stdexcept>

void Connection::sendMessage()
{
    m_iSendResult = send(m_ConnectSocket, m_recvbuf, m_iResult, 0);
    if (m_iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        // closesocket(m_ConnectSocket);
        WSACleanup();
        return 1;
    }
    printf("Bytes sent: %d\n", m_iSendResult);
}

void Connection::receiveMessage()
{
    im_result = recv(m_ConnectSocket, recvbuf, recvbuflen, 0);
    if (im_result > 0)
        printf("Bytes received: %d\n", im_result);
    else if (im_result == 0)
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());
}

Connection::Connection()
{
    // Initialize Winsock
    WSADATA wsaData;
    m_iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (m_iResult != 0) {
        std::string error = "WSAStartup failed with error: " + m_iResult;
        error.append("\n");
        throw std::runtime_error(error);
    }

    ZeroMemory(&m_hints, sizeof(m_hints));
    m_hints.ai_family = AF_INET;
    m_hints.ai_socktype = SOCK_STREAM;
    m_hints.ai_protocol = IPPROTO_TCP;
    m_hints.ai_flags = AI_PASSIVE;

    // Resolve the Server address and port
    m_iResult = getaddrinfo(NULL, DEFAULT_PORT, &m_hints, &m_result);
    if (m_iResult != 0) {
        std::string error = "getaddrinfo failed with error: " + m_iResult;
        error.append("\n");
        throw std::runtime_error(error);
        WSACleanup();
    }


}

Connection::~Connection()
{

    closesocket(m_ConnectSocket);
}
