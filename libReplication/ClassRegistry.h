#pragma once
#include <map>
#include <NetworkObject.h>
#include <functional>

namespace uqac {
	namespace replication {

		class ClassRegistry {
		public:
			template<class T>
			void RegisterClass() {
				m_idToConstructors[T::m_classID] = T::Create;
			}

			static ClassRegistry& Get();
			NetworkObject* Create(ClassID classID);

		private:
			ClassRegistry() {}
			std::map<ClassID, std::function<NetworkObject* ()>> m_idToConstructors;

		};
	}
}