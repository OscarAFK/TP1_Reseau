#pragma once
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "Connection.h"
#include "Terminal.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


class Server
{
private:

    Terminal    *my_terminal;
    Connection  *m_connectionClient;

public:


    Server() = default;       // Constructeur
    Server(char * port);       // Constructeur
    ~Server();      // Destructeur


    int runServer();

};