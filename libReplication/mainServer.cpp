#include <ReplicationManager.h>
#include <LinkingContext.h>
#include <Enemy.h>
#include <PlayerTP3.h>

#include <server.h>
#include <client.h>

int main(int argc, char** argv) {

	// Validate the parameters
	if (argc != 2) {
		std::cout << "usage: " << argv[0] << " port" << std::endl;
		return 1;
	}

	//On créer dans un premier temps un objet de type serveur, et on lance dans un nouveau thread l'attente de connexion.
	std::shared_ptr<uqac::Server> my_server = std::make_shared<uqac::Server>("TCP", argv[1],
		//A REFAIRE LES TROIS CALLBACKS
		[](uqac::Connection* c) { std::cout << "Client connected." << std::endl; },
		[&](uqac::Connection* c, char* recvBuffer) { std::cout << "Broadcasting message: " << recvBuffer << std::endl; my_server->broadcast(recvBuffer, c); },
		[](uqac::Connection* c) { std::cout << "Client disconnected." << std::endl; });


	uqac::replication::LinkingContext lCSend = uqac::replication::LinkingContext();
	uqac::replication::LinkingContext lCRecv = uqac::replication::LinkingContext();

	auto rMSend = uqac::replication::ReplicationManager(&lCSend);
	auto rMRecv = uqac::replication::ReplicationManager(&lCRecv);

	std::vector<uqac::utilsTP3::NetworkObject*> world;
	world.push_back(&uqac::utilsTP3::Enemy::generateRandomEnemy());
	world.push_back(&uqac::utilsTP3::Enemy::generateRandomEnemy());
	world.push_back(&uqac::utilsTP3::Enemy::generateRandomEnemy());

	for each (auto e in world)
	{
		e->Print();
	}

	uqac::serialization::Serializer s = uqac::serialization::Serializer();

	rMSend.SendWorld(world, &s);

	uqac::serialization::Deserializer d = uqac::serialization::Deserializer(s.getContainer(), s.getContainer()->size());

	rMRecv.RecvWorld(&d);

	for (int i = 0; i<3; i++)
	{
		auto nO = lCRecv.getNetworkObject(i);
		if (nO)
			nO.value()->Print();
	}

	return 0;
}


void UpdatePlayer(Player& player) {

	Vector3 position();
player = new Player(Vec )

}




