#pragma once

#include <map>
#include "../utils/framework.h"
#include "../utils/NetworkObject.h"
#include <optional>
#include <vector>
#include "LinkingContext.h"

class ReplicationManager {

public:
    void ReplicateWorldState(OutputMemoryBitStream& inStream,
        const vector<GameObject*>& inAllObjects);
private:
    void ReplicateIntoStream(OutputMemoryBitStream& inStream,
        GameObject* inGameObject);

    LinkingContext* mLinkingContext;
};

class ReplicationManager {
public:
	void ReceiveReplicatedObects(InputMemoryBitStream& inStream);
private:
	GameObject* ReceiveReplicatedObject(InputMemoryBitStream& inStream);
	
    unordered_set<GameObject*> mObjectsReplicatedToMe;
};