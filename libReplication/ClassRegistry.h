#pragma once
#include <map>
#include <NetworkObject.h>
#include <functional>
#include <Enemy.h>
#include <PlayerTP3.h>
#include <NetworkObject.h>

namespace uqac {
	namespace replication {

		class ClassRegistry {
		public:
			template<class T>
			void RegisterClass() {
				m_idToConstructors[T::m_classID] = T::Create;
			}

			static ClassRegistry& Get();
			utilsTP3::NetworkObject* Create(uint8_t classID);

		private:
			ClassRegistry() { PopulateIdToConstructors(); }

			void PopulateIdToConstructors();

			std::map<uint8_t, std::function<utilsTP3::NetworkObject* ()>> m_idToConstructors;

		};
	}
}