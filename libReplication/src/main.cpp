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
	
	//Vue que la partie r�seau ne fonctionne pas, on va juste montrer que la logique de r�plication fonctionne
	/*while (true) {
		rMSend.Update(world);
	}*/

	for each (auto e in world)
	{
		e->Print();
	}

	uqac::serialization::Serializer s = uqac::serialization::Serializer();

	//Cette fonction n'envoie pas vraiment le monde, elle se contente de le r�pliquer dans le stream
	rMSend.SendWorld(world, &s);

	//Ici on r�cup�re directement le container du Serializer dans le deserializer, mais si on devait int�grer du r�seau on lui passerait la chaine de caract�res re�ue
	uqac::serialization::Deserializer d = uqac::serialization::Deserializer(s.getContainer(), s.getContainer()->size());

	//On deserialize, d�compresse et r�plique le monde
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


