#include <ReplicationManager.h>
#include <LinkingContext.h>
#include <Enemy.h>

void main() {
	uqac::replication::LinkingContext lC = uqac::replication::LinkingContext();

	auto rM = uqac::replication::ReplicationManager(&lC);

	std::vector<uqac::utils::NetworkObject*> world;
	//world.push_back(new uqac::replication::Enemy())

	//rM.SendWorld();
}