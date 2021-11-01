#include "ReplicationManager.h"

namespace uqac {
	namespace replication {

		void ReplicationManager::Update(std::vector<utilsTP3::NetworkObject*> alloR, serialization::Serializer* s, serialization::Deserializer* d)
		{
			SendWorld(alloR, s);

			RecvWorld(d);
		}

		void ReplicationManager::SendWorld(std::vector<utilsTP3::NetworkObject*> alloR, serialization::Serializer* s)
		{
			/////////On réplique le monde
			//Tout les objets à répliquer
			for each (utilsTP3::NetworkObject * oR in alloR)
			{
				SerializeObject(s, oR);
			}
		}

		void ReplicationManager::RecvWorld(serialization::Deserializer* d)
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

		void ReplicationManager::SerializeObject(serialization::Serializer* s, utilsTP3::NetworkObject* oR)
		{
			//Serialize the network ID
			std::optional<int> nO = m_linkingContext->getNetworkId(oR);
			s->Serialize(*nO);

			//Serialize the class ID
			oR->utilsTP3::NetworkObject::Write(s);

			//Serialize the object
			oR->Write(s);
		}

		utilsTP3::NetworkObject* ReplicationManager::DeserializeObject(serialization::Deserializer* d)
		{
			int nId = d->Read<int>();
			int cId = d->Read<int>();

			std::optional<utilsTP3::NetworkObject*> nO = m_linkingContext->getNetworkObject(nId);
			if (!nO) {
				nO = ClassRegistry::Get().Create(utils::ClassID(cId));
				m_linkingContext->addNetworkObject(nO.value());
			}
			nO.value()->Read(d);
			return (nO.value());
		}
	}
}