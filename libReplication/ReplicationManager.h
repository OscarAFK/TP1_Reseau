#pragma once

#include <map>
#include <framework.h>
#include <NetworkObject.h>
#include <optional>
#include <vector>
#include "LinkingContext.h"
#include <unordered_set>

enum class PacketType : uint8_t {
    Hello = 0x00,
    Sync = 0x01,
    Bye = 0x02,
    PacketType_Max
};

class ReplicationManager {

public:
    void Update(std::vector<NetworkObject*> alloR, Serializer *s, Deserializer* d);

private:
    void SerializeObject(Serializer *s, NetworkObject* oR);
    void DeserializeObject(Deserializer *d);
    //void CreateObject(Serializer *s, NetworkObject* oR);

    std::unordered_set<NetworkObject*> m_objectsReplicated;
    LinkingContext* m_linkingContext;
};