#include <client.h>

int client::initialisationWinsock()
{
    this->m_iResult = WSAStartup(MAKEWORD(2, 2), &this->m_wsaData);
    if (this->m_iResult != 0) {
        printf("WSAStartup failed with error: %d\n", this->m_iResult);
        return 1;
    }
    return 0;
}
int client::getaddrinfo() {
    this->m_iResult = getaddrinfo(argv[1], DEFAULT_PORT, &this->m_hints, &this->m_result);
    if (this->m_iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", this->m_iResult);
        WSACleanup();
        return 1;
    }
    return 0;
}

int client::createSocket() {
    this->m_ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol);
    if (this->m_ConnectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    return 0;
}

void client::connectServeur() {
    this->m_iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (this->m_iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        continue;
    }
    break;
}

int client::initBuffer() {
    this->m_iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (this->m_iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    return 0;
    printf("Bytes Sent: %ld\n", iResult);
}

int client::connexionShutdown() {
    this->m_iResult = shutdown(ConnectSocket, SD_SEND);
    if (this->m_iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

void Client::runClient() {
    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    initialisationWinsock();

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    getaddrinfo();

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        createSocket();

        // Connect to server.
        connectServeur();
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    initBuffer();

    // shutdown the connection since no more data will be sent
    connexionShutdown();

    // Receive until the peer closes the connection
    do {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (iResult > 0);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}

