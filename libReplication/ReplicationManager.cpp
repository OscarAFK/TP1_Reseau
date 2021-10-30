#include "ReplicationManager.h"

void ReplicationManager::ReplicateIntoStream(
	OutputMemoryBitStream& inStream,
	GameObject* inGameObject)
{
	// wrtie game obj ID
	inStream.Write(mLinkingContext->GetNetworkId(inGameObject, true));

	// write game obj class
	inStream.Write(inGameObject->GetClassId());

	// write game object data
	inGameObject->Write(inStream);
}

void ReplicationManager::ReplicateWorldState(
	OutputMemoryBitStream& inStream,
	const vector<GameObject*>& inAllObjects)
{
	// tag as replication data
	inStream.WriteBits(PT_ReplicationData, GetRequiredBits<PT_MAW>::Value);

	// write each obj
	for (GameObject* obj : inAllObjects) {
		ReplicateIntoStream(inStream, obj);
	}
}



void ReplicationManager::ReceiveReplicatedObects(InputMemoryBitStream& inStream) 
{
	unordered_set<GameObject*> receivedObjects;
	
	while (inStream.GetRemainingBitCount() > 0) 
	{
		GameObject* receivedGameObject = ReceiveReplicatedObject(inStream);
		receivedObjects.insert(receivedGameObject);
	}

	//now run through mObjectsReplicatedToMe.
	//if an objject insn't in the recently replicated set,
	//destroy it
	for (GameObject* go : mObjectsReplicateToMe)
	{
		if (receivedObjects.find(go) != receivedGameObject.end()) 
		{
			mLinkingContext->Remove(go);
			go->Destroy();
		}
	}

	mObjectReplicatedToMe = receivedObjects;
}

GameObject* ReplicationManager::ReceiveReplicatedObject(InputMemoryBitStream& inStream)
{
	uint32_t networId;
	uint32_t classId;
	inStream.Read(networdId);
	inStream.Read(classid);

	GameObject* go = mLinkingContext->GetGameObject(networkId);
	if (!go) 
	{
		go = ObjectCreationRegistry::Get().CreateGameObject(classId);
		mLinkingContext->AddGameObject(go, networkId);
	}

	//now read update
	go->Read(inStream);

	//return gameobject so we can track it was received in pacet
	return go;
}