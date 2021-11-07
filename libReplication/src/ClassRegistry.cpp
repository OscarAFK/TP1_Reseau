#include <include/ClassRegistry.h>

namespace uqac {
	namespace replication {

		ClassRegistry& ClassRegistry::Get()
		{
			static ClassRegistry cR;
			return cR;
		}

		utilsTP3::NetworkObject* ClassRegistry::Create(uint8_t classID)
		{
			std::function<utilsTP3::NetworkObject* ()> constructor = m_idToConstructors[classID];
			utilsTP3::NetworkObject* nO = constructor();
			return nO;
		}
		void ClassRegistry::PopulateIdToConstructors()
		{
			RegisterClass<utilsTP3::Enemy>();
			RegisterClass<utilsTP3::Player>();
		}
	}
}