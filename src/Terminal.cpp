#include "Terminal.h"
#include "Connection.h"


Terminal::Terminal(int listenSocket) : m_ListenSocket(listenSocket)
{
}


Connection * Terminal::Connect()
{
    // Accept a client socket
    int ConnectSocket = accept(m_ListenSocket, NULL, NULL);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(m_ListenSocket);
        WSACleanup();
    }
    return new Connection(ConnectSocket);
}
