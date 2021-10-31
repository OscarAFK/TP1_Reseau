#pragma once

#include <map>
#include <framework.h>
#include <NetworkObject.h>
#include <optional>
#include <vector>
#include "LinkingContext.h"
#include <unordered_set>
#include <ClassRegistry.h>

enum class PacketType : uint8_t {
    Hello = 0x00,
    Sync = 0x01,
    Bye = 0x02,
    PacketType_Max
};

class ReplicationManager {
public:
    ReplicationManager(LinkingContext* linkingContext) : m_linkingContext(linkingContext) {};
    ~ReplicationManager() = default;

    void Update(std::vector<NetworkObject*> alloR, Serializer *s, Deserializer* d);
    void SendWorld(std::vector<NetworkObject*> alloR, Serializer* s);
    void RecvWorld(Deserializer* d);

private:
    void SerializeObject(Serializer *s, NetworkObject* oR);
    NetworkObject * DeserializeObject(Deserializer *d);

    std::unordered_set<NetworkObject*> m_objectsReplicated;
    LinkingContext* m_linkingContext;
};