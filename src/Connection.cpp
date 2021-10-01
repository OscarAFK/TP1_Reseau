#include "Connection.h"
#include <stdio.h>
#include <stdexcept>

void Connection::sendMessage()
{
    m_iResult = send(m_ConnectSocket, m_recvbuf, m_iResult, 0);
    if (m_iResult == SOCKET_ERROR) {
        std::string error = "send failed with error: " + WSAGetLastError();
        error.append("\n");
        throw std::runtime_error(error);
        WSACleanup();
    }
    printf("Bytes sent: %d\n", m_iResult);
}

void Connection::receiveMessage()
{
    m_iResult = recv(m_ConnectSocket, m_recvbuf, m_recvbuflen, 0);
    if (m_iResult > 0)
        printf("Bytes received: %d\n", m_iResult);
    else if (m_iResult == 0)
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());
}

Connection::Connection(char* addr, char* port)
{
    WSADATA wsaData;
    m_iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (m_iResult != 0) {
        std::string error = "WSAStartup failed with error: " + m_iResult;
        error.append("\n");
        throw std::runtime_error(error);
    }

    if (port == NULL)
        port = DEFAULT_PORT;

    m_iResult = getaddrinfo(addr, port, &m_hints, &m_result);
    if (m_iResult != 0) {
        std::string error = "getaddrinfo failed with error: " + m_iResult;
        error.append("\n");
        throw std::runtime_error(error);
        WSACleanup();
    }

    //Create a SOCKET for connecting to the server
    m_ConnectSocket = socket(m_ptr->ai_family, m_ptr->ai_socktype,
        m_ptr->ai_protocol);
    if (m_ConnectSocket == INVALID_SOCKET) {
        std::string error = "socket failed with error: " + m_iResult;
        error.append("\n");
        throw std::runtime_error(error);
        WSACleanup();
    }

    // Connect to server.
    m_iResult = connect(m_ConnectSocket, m_ptr->ai_addr, (int)m_ptr->ai_addrlen);
    if (m_iResult == SOCKET_ERROR) {
        closesocket(m_ConnectSocket);
        m_ConnectSocket = INVALID_SOCKET;
        throw std::runtime_error("Couldn't connect to the server");
    }

    ////////TOUT CA EST A METTRE DANS LA CLASSE TERMINAL
    //// Initialize Winsock
    //WSADATA wsaData;
    //m_iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    //if (m_iResult != 0) {
    //    std::string error = "WSAStartup failed with error: " + m_iResult;
    //    error.append("\n");
    //    throw std::runtime_error(error);
    //}

    //ZeroMemory(&m_hints, sizeof(m_hints));
    //m_hints.ai_family = AF_INET;
    //m_hints.ai_socktype = SOCK_STREAM;
    //m_hints.ai_protocol = IPPROTO_TCP;
    //m_hints.ai_flags = AI_PASSIVE;

    //// Resolve the Server address and port
    //if (port == NULL)
    //    port = DEFAULT_PORT;

    //m_iResult = getaddrinfo(addr, port, &m_hints, &m_result);
    //if (m_iResult != 0) {
    //    std::string error = "getaddrinfo failed with error: " + m_iResult;
    //    error.append("\n");
    //    throw std::runtime_error(error);
    //    WSACleanup();
    //}

    //// Create a SOCKET for connecting to Server
    //m_ListenSocket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
    //if (m_ListenSocket == INVALID_SOCKET) {
    //    std::string error = "socket failed with error: " + WSAGetLastError();
    //    error.append("\n");
    //    throw std::runtime_error(error);
    //    freeaddrinfo(m_result);
    //    WSACleanup();
    //}



}

Connection::~Connection()
{

    closesocket(m_ListenSocket);
    closesocket(m_ConnectSocket);
}
