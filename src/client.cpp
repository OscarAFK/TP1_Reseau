#include "client.h"

int Client::initialisationWinsock()
{
    m_iResult = WSAStartup(MAKEWORD(2, 2), &this->m_wsaData);
    if (m_iResult != 0) {
        printf("WSAStartup failed with error: %d\n", m_iResult);
        return 1;
    }
    return 0;
}
int Client::Getaddrinfo(char* addr) {
    m_iResult = getaddrinfo(addr, DEFAULT_PORT, &m_hints, &m_result);
    if (m_iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", m_iResult);
        WSACleanup();
        return 1;
    }
    return 0;
}

int Client::createSocket() {
    m_ConnectSocket = socket(m_ptr->ai_family, m_ptr->ai_socktype,
        m_ptr->ai_protocol);
    if (m_ConnectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    return 0;
}

int Client::connectServeur() {
    m_iResult = connect(m_ConnectSocket, m_ptr->ai_addr, (int)m_ptr->ai_addrlen);
    if (m_iResult == SOCKET_ERROR) {
        closesocket(m_ConnectSocket);
        m_ConnectSocket = INVALID_SOCKET;
        return 1;
    }
    return 0;
}

int Client::initBuffer() {
    m_iResult = send(m_ConnectSocket, m_sendbuf, (int)strlen(m_sendbuf), 0);
    if (m_iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(m_ConnectSocket);
        WSACleanup();
        return 1;
    }
    return 0;
    printf("Bytes Sent: %ld\n", m_iResult);
}

int Client::connexionShutdown() {
    m_iResult = shutdown(m_ConnectSocket, SD_SEND);
    if (m_iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(m_ConnectSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int Client::runClient() {
    
    // Initialize Winsock
    initialisationWinsock();

    ZeroMemory(&m_hints, sizeof(m_hints));
    m_hints.ai_family = AF_UNSPEC;
    m_hints.ai_socktype = SOCK_STREAM;
    m_hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    Getaddrinfo("127.0.0.1");

    // Attempt to connect to an address until one succeeds
    for (m_ptr = m_result; m_ptr != NULL; m_ptr = m_ptr->ai_next) {

        // Create a SOCKET for connecting to server
        createSocket();

        // Connect to server.
        connectServeur();
    }

    freeaddrinfo(m_result);

    if (m_ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    initBuffer();

    // shutdown the connection since no more data will be sent
    connexionShutdown();

    // Receive until the peer closes the connection
    /*do {
        im_result = recv(m_ConnectSocket, recvbuf, recvbuflen, 0);
        if (im_result > 0)
            printf("Bytes received: %d\n", im_result);
        else if (im_result == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (im_result > 0);*/

    // cleanup
    closesocket(m_ConnectSocket);
    WSACleanup();
    return 0;
}

