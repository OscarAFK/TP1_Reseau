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
	Client my_client1 = Client("localhost", NULL);
	Client my_client2 = Client("localhost", NULL);
	std::thread th_client1(&Client::runClient, &my_client1);
	std::thread th_client2(&Client::runClient, &my_client2);

	
	th_client1.join();
	th_client2.join();
	th_server.join();

	std::cout << "server and client stopped.\n";

	return 0;

}