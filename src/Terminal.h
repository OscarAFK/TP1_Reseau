#pragma once
#include "Connection.h"

// permet au serveur de créer une connexion lorsqu’il reçoit une
// demande de connexion d’un client.
class Terminal {


public :

	Connection createConnection();
};