#pragma once
#include "Connection.h"

// permet au serveur de cr�er une connexion lorsqu�il re�oit une
// demande de connexion d�un client.
class Terminal {


public :

	Connection createConnection();
};