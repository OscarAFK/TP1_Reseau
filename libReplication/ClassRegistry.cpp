#include "ClassRegistry.h"

ClassRegistry& ClassRegistry::Get()
{
	static ClassRegistry cR;
	return cR;
}

NetworkObject* ClassRegistry::Create(ClassID classID)
{
	std::function<NetworkObject*()> constructor = m_idToConstructors[classID];
	return constructor();
}
