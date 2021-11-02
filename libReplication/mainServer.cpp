#include <ReplicationManager.h>
#include <LinkingContext.h>
#include <Enemy.h>

void main() {
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
}