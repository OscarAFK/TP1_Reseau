#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

#include "server.h"
#include "client.h"
#include "Connection.h"
#include "Terminal.h"

int main() {

	Terminal my_terminal;

	Client my_client;
	Server my_server;

	my_server.setConnection(my_terminal.createConnection());
	my_client.setConnection(my_terminal.createConnection());
	

	std::thread th_server(&Server::RunServer, &my_server);
	std::thread th_client(&Client::runClient, &my_client);
	

	th_client.join();
	th_server.join();

	std::cout << "server and client stopped.\n";

	return 0;

}