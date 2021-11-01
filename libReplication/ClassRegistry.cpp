#include "ClassRegistry.h"
namespace uqac {
	namespace replication {

		ClassRegistry& ClassRegistry::Get()
		{
			static ClassRegistry cR;
			return cR;
		}

		utilsTP3::NetworkObject* ClassRegistry::Create(utils::ClassID classID)
		{
			std::function<utilsTP3::NetworkObject* ()> constructor = m_idToConstructors[classID];
			return constructor();
		}
	}
}