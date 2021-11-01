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
			utilsTP3::NetworkObject* Create(utils::ClassID classID);

		private:
			ClassRegistry() {}
			std::map<utils::ClassID, std::function<utilsTP3::NetworkObject* ()>> m_idToConstructors;

		};
	}
}