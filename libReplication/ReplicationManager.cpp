#include "ReplicationManager.h"

void ReplicationManager::Update(std::vector<NetworkObject*> alloR, Serializer* s, Deserializer* d)
{
	/////////On réplique le monde

	//On ne s'occupe pas encore de l'identifiant du protocole

	//Le type du packet
	uint8_t pTSend = (uint8_t)PacketType::Sync;
	s->Serialize(pTSend);

	//Tout les objets à répliquer
	for each (NetworkObject* oR in alloR)
	{
		SerializeObject(s, oR);
	}
	
	//La taille du packet
	v.insert(v.begin() + i, valueToInsert);

	/////////On reçoit le monde

	//On vérifie le type du packet
	PacketType pTRecv = PacketType(d->Read<uint8_t>());
	if (pTRecv == PacketType::Sync) {

		std::unordered_set<NetworkObject*> objectRecv;


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

void ReplicationManager::DeserializeObject(Deserializer* d)
{

}
