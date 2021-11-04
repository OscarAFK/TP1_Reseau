#pragma once

#include <map>
#include <frameworkTP3.h>
#include <NetworkObject.h>
#include <optional>
#include <vector>
#include "LinkingContext.h"
#include <unordered_set>
#include <ClassRegistry.h>
#include <server.h>
#include <client.h>

namespace uqac {
    namespace replication {

        enum class PacketType : uint8_t {
            Hello = 0x00,
            Sync = 0x01,
            Bye = 0x02,
            PacketType_Max
        };

        class ReplicationManager {
        public:
            ReplicationManager(LinkingContext* linkingContext, std::string typeNetwork, std::string protocole, std::string addr, std::string port);
            ~ReplicationManager() = default;

            void Update(std::vector<utilsTP3::NetworkObject*> alloR, std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);
            void SendWorld(std::vector<utilsTP3::NetworkObject*> alloR, serialization::Serializer* s);
            void RecvWorld(serialization::Deserializer* d);

        private:
            void SerializeObject(serialization::Serializer* s, utilsTP3::NetworkObject* oR);
            void DeserializeObject(serialization::Deserializer* d);

            std::unordered_set<utilsTP3::NetworkObject*> m_objectsReplicated;
            LinkingContext* m_linkingContext;
            std::shared_ptr<uqac::Network> m_network;
        };
    }
}