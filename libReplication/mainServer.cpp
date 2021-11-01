#include <ReplicationManager.h>
#include <LinkingContext.h>
#include <Enemy.h>

void main() {
	uqac::replication::LinkingContext lC = uqac::replication::LinkingContext();

	auto rM = uqac::replication::ReplicationManager(&lC);

	std::vector<uqac::utilsTP3::NetworkObject*> world;
	world.push_back(&uqac::utilsTP3::Enemy::generateRandomEnemy());
	world.push_back(&uqac::utilsTP3::Enemy::generateRandomEnemy());
	world.push_back(&uqac::utilsTP3::Enemy::generateRandomEnemy());

	for each (auto e in world)
	{
		e->Print();
	}

	uqac::serialization::Serializer s = uqac::serialization::Serializer();

	rM.SendWorld(world, &s);

	uqac::serialization::Deserializer d = uqac::serialization::Deserializer(s.getContainer(), s.getContainer()->size());

	rM.RecvWorld(&d);

	for (int i = 0; i<3; i++)
	{
		auto nO = lC.getNetworkObject(i);
		if (nO)
			nO.value()->Print();
	}
}