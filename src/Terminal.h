#pragma once
#include "Connection.h"

#include <stdlib.h>
#include <stdio.h>


#include "SocketManager.h"

// permet au serveur de créer une connexion lorsqu’il reçoit une
// demande de connexion d’un client.
class Terminal : public SocketManager {

private:

	//int m_ListenSocket = NULL;
	int m_iResult;

public :

	//Terminal(int listenSocket);
	Terminal(std::string protocole, std::string port);
	Terminal() = default;
	~Terminal() = default;

	int Connect();
};