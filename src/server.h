#pragma once
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Connection.h"
#include "Terminal.h"
#include "Network.h"

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

public:

    Server() = default;       // Constructeur
    Server(char * port);       // Constructeur
    ~Server();      // Destructeur

    void readSockets();
    int Update();

};