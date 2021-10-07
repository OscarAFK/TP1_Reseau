#pragma once
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <atomic>

#include "UDPConnection.h"
#include "TCPConnection.h"
#include "Terminal.h"
#include "Network.h"
#include <thread>
#include <functional>

class Server : public Network {

public:


    Server() = default;       // Constructeur
    Server(std::string protocole, std::string port, std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);       // Constructeur
    ~Server();      // Destructeur

    void Listen(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char *)> onRecv, std::function<void(Connection*)> onDisconnect);
    

};