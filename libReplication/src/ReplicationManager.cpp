#include <include/ReplicationManager.h>

namespace uqac {
	namespace replication {
		ReplicationManager::ReplicationManager(LinkingContext* linkingContext, std::string typeNetwork, std::string protocole, std::string addr, std::string port) : m_linkingContext(linkingContext)
		{
			uqac::network::Config config;

			endpoint = protocole + "//"+ addr + ":" + port;
			m_network = std::make_shared<uqac::network::UQACNetwork>();
			if (typeNetwork == "s") {
				isServer = true;

				config.OnConnect = [](uqac::network::ConnectionWeakPtr connection) {
					std::cout << "SERVER OnConnect" << std::endl;
				};

				config.OnReceive = [](uqac::network::ConnectionWeakPtr connection, char* buffer, size_t size) {
					std::cout << "SERVER OnReceive";
				};

				m_terminal = m_network->Listen(endpoint, config).lock();


			}
			else {
				isServer = false;
				int id = 1;
				config.OnReceive = [id](uqac::network::ConnectionWeakPtr connection, char* buffer, size_t size) {
					std::cout << "OnReceive";
				};

				auto connection = m_network->Connect(endpoint, config);
				if (auto c = connection.lock()) { // Has to be copied into a shared_ptr before usage
					auto msg = "HELLO WORLD ! FROM " + std::to_string(id);
					c->Send(msg.data(), msg.length());

				}

			}
		}
		
		void ReplicationManager::Update(std::vector<utilsTP3::NetworkObject*> alloR)
		{
			std::function<void(uqac::network::ConnectionWeakPtr connection, char* buffer, size_t size)> onRecvReplicate;
			std::string sRecvBuff;
			m_network->Update(50ms);
			if (isServer) {
				serialization::Serializer s = uqac::serialization::Serializer();

				SendWorld(alloR, &s);
				auto sendBuff = s.getContainer();
				std::string sSendBuff(sendBuff->begin(), sendBuff->end());

				
				auto ter = m_terminal.lock();
				if (ter) {
					for each (auto & c in ter->GetAllConnection()) {
						c.second->Send(sSendBuff.data(), sSendBuff.size());
					}
				}
				
			}

			if (!isServer) {
				
				std::vector<char> recvBuff(sRecvBuff.begin(), sRecvBuff.end());

				serialization::Deserializer d = uqac::serialization::Deserializer(&recvBuff, recvBuff.size());

				RecvWorld(&d);
			}

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
			if (!nO) {
				m_linkingContext->addNetworkObject(oR);
			}
			nO = m_linkingContext->getNetworkId(oR);
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