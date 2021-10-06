#pragma once
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <atomic>

#include "Connection.h"
#include "Terminal.h"
#include "Network.h"
#include <thread>
#include <functional>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


class Server
{
private:

    Terminal                    *m_terminal;
    std::vector<Connection*>    m_connectionsClients;
    std::thread m_threadNetwork;
    std::atomic<bool> m_quit;

public:


    Server() = default;       // Constructeur
    Server(std::string port, std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);       // Constructeur
    ~Server();      // Destructeur

    void readSockets(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char *)> onRecv, std::function<void(Connection*)> onDisconnect);
    void broadcast(const std::string message);
    void broadcast(const std::string message, const Connection* origin);
    int Update(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char *)> onRecv, std::function<void(Connection*)> onDisconnect);
    void Quit();

};