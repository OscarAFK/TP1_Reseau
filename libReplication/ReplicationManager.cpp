#include "ReplicationManager.h"

void ReplicationManager::Update(std::vector<NetworkObject*> alloR, Serializer* s, Deserializer* d)
{
	SendWorld(alloR, s);

	RecvWorld(d);
}

void ReplicationManager::SendWorld(std::vector<NetworkObject*> alloR, Serializer* s)
{
	/////////On réplique le monde
	//Tout les objets à répliquer
	for each (NetworkObject * oR in alloR)
	{
		SerializeObject(s, oR);
	}
}

void ReplicationManager::RecvWorld(Deserializer* d)
{
	/////////On reçoit le monde
	//On vérifie le type du packet
	PacketType pTRecv = PacketType(d->Read<uint8_t>());
	if (pTRecv == PacketType::Sync) {
		while (!d->isBufferCompletelyRead()) {
			auto nO = DeserializeObject(d);
			m_objectsReplicated.insert(nO);
		}
	}
}

void ReplicationManager::SerializeObject(Serializer *s, NetworkObject* oR)
{
	//Serialize the network ID
	std::optional<int> nO = m_linkingContext->getNetworkId(oR);
	s->Serialize(*nO);

	//Serialize the class ID
	oR->NetworkObject::Write(s);

	//Serialize the object
	oR->Write(s);
}

NetworkObject* ReplicationManager::DeserializeObject(Deserializer* d)
{
	int nId = d->Read<int>();
	int cId = d->Read<int>();

	std::optional<NetworkObject*> nO = m_linkingContext->getNetworkObject(nId);
	if (!nO) {
		nO = ClassRegistry::Get().Create(ClassID(cId));
		m_linkingContext->addNetworkObject(*nO);
	}
	(*nO)->Read(d);
	return (*nO);
}
