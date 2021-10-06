#pragma once
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Connection.h"
#include <thread>
#include <functional>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class Client {
	public:

		Client() = default;		// constructeur
		Client(std::string addr, std::string port, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);		// constructeur
		~Client();		// destructeur

		int Update(std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);
		void readSocket(std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);
		void sendMessage(const std::string message);
		bool isServerUp();
		void Quit();



	private:
		bool quit;
		Connection* m_connection;
		std::thread m_threadNetwork;
};