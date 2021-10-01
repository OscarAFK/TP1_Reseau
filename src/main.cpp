#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

#include "server.h"
#include "Connection.h"
#include "Terminal.h"

int main() {
	//auto s = server();

	Terminal my_terminal;

	Client my_client;
	Server my_server;

	my_client.setConnection(my_terminal.createConnection());
	my_server.setConnection(my_terminal.createConnection());

	std::thread th_client(my_client.runClient());
	std::thread th_server(my_server.RunServer());

	th_client.join();
	th_server.join();

	std::cout << "server and client completed.\n";

	return 0;

}