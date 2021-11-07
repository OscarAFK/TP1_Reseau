#include <include/ReplicationManager.h>
#include <include/LinkingContext.h>
#include <Enemy.h>
#include <PlayerTP3.h>

int main(int argc, char** argv) {


	uqac::replication::LinkingContext lCSend = uqac::replication::LinkingContext();
	uqac::replication::LinkingContext lCRecv = uqac::replication::LinkingContext();

	auto rMSend = uqac::replication::ReplicationManager(&lCSend, "s", "tcp", "localhost", "42666");
	auto rMRecv = uqac::replication::ReplicationManager(&lCRecv, "c", "tcp", "localhost", "42666");

	std::vector<uqac::utilsTP3::NetworkObject*> world;
	world.push_back(&uqac::utilsTP3::Enemy::generateRandomEnemy());
	world.push_back(&uqac::utilsTP3::Enemy::generateRandomEnemy());
	
	//Vue que la partie réseau ne fonctionne pas, on va juste montrer que la logique de réplication fonctionne
	/*while (true) {
		rMSend.Update(world);
	}*/

	for each (auto e in world)
	{
		e->Print();
	}

	uqac::serialization::Serializer s = uqac::serialization::Serializer();

	//Cette fonction n'envoie pas vraiment le monde, elle se contente de le répliquer dans le stream
	rMSend.SendWorld(world, &s);

	//Ici on récupère directement le container du Serializer dans le deserializer, mais si on devait intégrer du réseau on lui passerait la chaine de caractères reçue
	uqac::serialization::Deserializer d = uqac::serialization::Deserializer(s.getContainer(), s.getContainer()->size());

	//On deserialize, décompresse et réplique le monde
	rMRecv.RecvWorld(&d);

	for (int i = 0; i < world.size(); i++)
	{
		auto nO = lCRecv.getNetworkObject(i);
		if (nO)
			nO.value()->Print();
	}



	return 0;
}
/*

void UpdatePlayer(Player& player) {

	Vector3 position();
player = new Player(Vec )

}

*/


