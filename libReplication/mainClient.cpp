#include <ReplicationManager.h>
#include <LinkingContext.h>
#include <Enemy.h>
#include <PlayerTP3.h>

#include "server.h"
#include "client.h"
#include <string>

int main(int argc, char** argv) {

	// Validate the parameters
	if (argc != 3) {
		std::cout << "usage: " << argv[0] << " adresse port" << std::endl;
		return 1;
	}

	uqac::replication::LinkingContext lC = uqac::replication::LinkingContext();
	auto rM = uqac::replication::ReplicationManager(&lC);

	//FINALEMENT pour l'instant on affichera ce qu'il y a dans le linking context dans un premier temps
	//std::vector<uqac::utilsTP3::NetworkObject*> world;	//Vide au début, se rempliera avec ce qui est présent sur le serveur
	

	//CALLBACKS à changer
	std::shared_ptr<uqac::Client> my_client = std::make_shared<uqac::Client>("TCP", argv[1], argv[2],
		[&](uqac::Connection* c, char* recvBuffer) { std::cout << "Received message: " << recvBuffer << std::endl; },
		[](uqac::Connection* c) { std::cout << "Server disconnected." << std::endl; });

	while (my_client->isServerUp()) {
		for (int i = 0; i < 3; i++)
		{
			auto nO = lC.getNetworkObject(i);
			if (nO)
				nO.value()->Print();
		}
	}
	if (!my_client->isServerUp()) {
		std::cout << "The server has been shut down, disconnecting the client" << std::endl;
	}
	my_client->Quit();

	return 0;

}

void recvWorld(uqac::Connection* c, char* recvBuffer, uqac::replication::ReplicationManager rM) {
	uqac::serialization::Deserializer d = uqac::serialization::Deserializer(recvBuffer, recvBuffer);
	rM.RecvWorld(&d);
}