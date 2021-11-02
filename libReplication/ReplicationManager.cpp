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

			while (!d->isBufferCompletelyRead()) {
				DeserializeObject(d);
			}

		}

		void ReplicationManager::SerializeObject(serialization::Serializer* s, utilsTP3::NetworkObject* oR)
		{
			//Serialize the network ID
			std::optional<uint32_t> nO = m_linkingContext->getNetworkId(oR);
			s->Serialize(*nO);

			//Serialize the class ID
			uint8_t cId = (uint8_t)oR->GetClassId();
			s->Serialize(cId);

			//Serialize the object
			oR->Write(s);
		}

		void ReplicationManager::DeserializeObject(serialization::Deserializer* d)
		{
			int nId = d->Read<int>();
			int cId = d->Read<uint8_t>();

			std::optional<utilsTP3::NetworkObject*> nO = m_linkingContext->getNetworkObject(nId);
			if (!nO) {
				nO = ClassRegistry::Get().Create(cId);
				m_linkingContext->addNetworkObject(nO.value());
			}
			nO.value()->Read(d);

			m_objectsReplicated.insert(nO.value());
		}
	}
}