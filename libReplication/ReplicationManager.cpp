#include "ReplicationManager.h"

namespace uqac {
	namespace replication {
		ReplicationManager::ReplicationManager(LinkingContext* linkingContext, std::string typeNetwork, std::string protocole, std::string addr, std::string port) : m_linkingContext(linkingContext)
		{
			if (typeNetwork == "s")
				m_network = std::make_shared<uqac::Server>(protocole, port);
			else 
				m_network = std::make_shared<uqac::Client>(protocole, addr, port);
		}
		
		void ReplicationManager::Update(std::vector<utilsTP3::NetworkObject*> alloR, std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect)
		{
			serialization::Serializer s = uqac::serialization::Serializer();

			SendWorld(alloR, &s);
			auto sendBuff = s.getContainer();
			std::string sSendBuff(sendBuff->begin(), sendBuff->end());
			m_network->broadcast(sSendBuff);

			std::string sRecvBuff;

			auto onRecvReplicate = [&](uqac::Connection* c, char* recvBuffer) 
			{
				sRecvBuff.assign(recvBuffer);
				onRecv(c, recvBuffer);
			};

			m_network->Listen(onConnect, onRecvReplicate, onDisconnect);

			std::vector<char> recvBuff(sRecvBuff.begin(), sRecvBuff.end());

			serialization::Deserializer d = uqac::serialization::Deserializer(&recvBuff, recvBuff.size());

			RecvWorld(&d);

		}

		void ReplicationManager::SendWorld(std::vector<utilsTP3::NetworkObject*> alloR, serialization::Serializer* s)
		{
			for each (utilsTP3::NetworkObject * oR in alloR)
			{
				SerializeObject(s, oR);
			}
		}

		void ReplicationManager::RecvWorld(serialization::Deserializer* d)
		{
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