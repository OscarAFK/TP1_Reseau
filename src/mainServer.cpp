#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "server.h"
#include "client.h"
#include <string>

int main() {

	
	char* port = NULL;	//Je suis obligé de passer par cette variable pour utiliser make_unique, sinon ça gueulait
	char* addr = "localhost";	//idem

	//On créer dans un premier temps un objet de type serveur, et on lance dans un nouveau thread l'attente de connexion.
	std::shared_ptr<Server> my_server = std::make_shared<Server>(port);

	std::string input = "";
	bool quit = false;

	printf( "===================================================================\n"
			"===\t8INF912 Programmation reseau dans les Jeux Video\t===\n"
			"===\t\t\tTP1 - Socket de Berkeley\t\t===\n"
			"===\tOscar Trosseau - Hippolyte Gossoin - Florent Bogacz\t===\n"
			"===\t\t\t\tSERVEUR\t\t\t\t===\n"
			"===\t\t\t\t\t\t\t\t===\n"
			"===\t\tEcrivez \"quit\" pour quitter l'application\t===\n"
			"===================================================================\n\n");

	while(quit == false) {
		std::cin >> input;

		if (input == "quit") {
			quit = true;
		}
	}
	my_server->Quit();

	return 0;
}