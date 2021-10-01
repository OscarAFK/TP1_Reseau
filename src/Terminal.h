#pragma once
#include "Connection.h"
#include "server.h"
#include "client.h"

// permet au serveur de cr�er une connexion lorsqu�il re�oit une
// demande de connexion d�un client.
class Terminal {

private:
	Server s;
	Client c; 

public :

	Terminal();
	~Terminal();

	Connection createConnection();
};