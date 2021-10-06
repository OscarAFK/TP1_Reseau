#include "Network.h"

int Network::getSocket()
{
    return m_ConnectSocket;
}

std::string Network::getName()
{
    struct sockaddr_in socketInfo = {0};
    int namelen = sizeof(sockaddr);
    getpeername(m_ConnectSocket, (struct sockaddr*)&socketInfo, &namelen);
    std::string name = inet_ntoa(socketInfo.sin_addr) + socketInfo.sin_port;
    return name;
}

void Network::Update()
{
}

Network::Network(std::string addr, std::string port) : verbose(true)
{
    // Initialize Winsock
    WSADATA wsaData;
    m_iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (m_iResult != 0) {
        if (verbose) std::cout << "WSAStartup failed with error: " << m_iResult << std::endl;
        return;
    }

    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the Server address and port
    if (port.empty())
        port = DEFAULT_PORT;

    if (addr.empty())
        addr = "localhost";

    m_iResult = getaddrinfo(addr.c_str(), port.c_str(), &hints, &m_result);
    if (m_iResult != 0) {
        if (verbose) std::cout << "getaddrinfo failed with error: " << m_iResult << std::endl;
        WSACleanup();
        return;
    }
}

Network::Network(int socket) : verbose(true)
{
    m_ConnectSocket = socket;
    u_long nonBlocking = 1;
    ioctlsocket(m_ConnectSocket, FIONBIO, &nonBlocking);
}

Network::~Network()
{
    if (m_ConnectSocket != INVALID_SOCKET) {
        m_iResult = shutdown(m_ConnectSocket, SD_SEND);
        if (verbose && m_iResult == SOCKET_ERROR) {
            std::cout << "Connection: shutdown failed with error: " << WSAGetLastError() << std::endl;
        }
    }
    closesocket(m_ConnectSocket);
    WSACleanup();
}
