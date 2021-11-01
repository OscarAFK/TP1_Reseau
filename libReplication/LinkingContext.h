#pragma once
#include <map>
#include <frameworkTP3.h>
#include <NetworkObject.h>
#include <optional>

namespace uqac {
	namespace replication {
		class LinkingContext {
		public:
			void addNetworkObject(utilsTP3::NetworkObject* nO);
			void removeNetworkObject(utilsTP3::NetworkObject* nO);

			std::optional<utilsTP3::NetworkObject*> getNetworkObject(int netId);
			std::optional<int> getNetworkId(utilsTP3::NetworkObject* nO);

			std::map<int, utilsTP3::NetworkObject*> m_idToPointer;
			std::map<utilsTP3::NetworkObject*, int> m_pointerToId;
		private:

			int m_nextNetworkID;

		};
	}
}

