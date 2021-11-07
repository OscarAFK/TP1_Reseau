#pragma once

#include <map>
#include <frameworkTP3.h>
#include <NetworkObject.h>
#include <optional>
#include <vector>
#include "LinkingContext.h"
#include <unordered_set>
#include <include/ClassRegistry.h>

#include "UQACNetwork/main/include/UQACNetwork/uqacNetwork.hpp"
#include "UQACNetwork/main/include/UQACNetwork/Terminal.hpp"
#include "UQACNetwork/main/include/UQACNetwork/Connection.hpp"

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

            void Update(std::vector<utilsTP3::NetworkObject*> alloR);
            void SendWorld(std::vector<utilsTP3::NetworkObject*> alloR, serialization::Serializer* s);
            void RecvWorld(serialization::Deserializer* d);

        private:
            void SerializeObject(serialization::Serializer* s, utilsTP3::NetworkObject* oR);
            void DeserializeObject(serialization::Deserializer* d);

            std::unordered_set<utilsTP3::NetworkObject*> m_objectsReplicated;
            LinkingContext* m_linkingContext;
            bool isServer;
            std::shared_ptr<uqac::network::UQACNetwork> m_network;
            std::string endpoint;
            uqac::network::TerminalWeakPtr m_terminal;

        };
    }
}