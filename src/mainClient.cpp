#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "server.h"
#include "client.h"
#include <string>

int main() {

	
	char* port = NULL;	//Je suis oblig� de passer par cette variable pour utiliser make_unique, sinon �a gueulait
	char* addr = "localhost";	//idem

	//On cr�er dans un premier temps un objet de type serveur, et on lance dans un nouveau thread l'attente de connexion.
	std::shared_ptr<Server> my_server = std::make_shared<Server>(port);
	
	//On cr�er un nouvel objet de type client, qui va juste envoyer un message au serveur
	std::shared_ptr<Client> my_client1 = std::make_shared<Client>(addr, port);
	std::shared_ptr<Client> my_client2 = std::make_shared<Client>(addr, port);

	my_client1->sendMessage("Hello World");
	
	return 0;

}