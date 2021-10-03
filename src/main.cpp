#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

#include "server.h"
#include "client.h"
#include "Connection.h"
#include "Terminal.h"
#include <string>

int main() {

	

	//On créer dans un premier temps un objet de type serveur, et on lance dans un nouveau thread l'attente de connexion.
	Server my_server = Server(NULL);
	std::thread th_server(&Server::runServer, &my_server);
	
	//On créer un nouvel objet de type client, qui va juste envoyer un message au serveur
	Client my_client = Client("localhost", NULL);
	my_client.runClient();

	th_server.join();
	

	std::cout << "server and client stopped.\n";

	return 0;

}