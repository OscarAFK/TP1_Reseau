#pragma once
#include <map>
#include <frameworkTP3.h>
#include <NetworkObject.h>
#include <optional>

namespace uqac {
	namespace replication {
		class LinkingContext {
		public:
			void addNetworkObject(NetworkObject* nO);
			void removeNetworkObject(NetworkObject* nO);

			std::optional<NetworkObject*> getNetworkObject(int netId);
			std::optional<int> getNetworkId(NetworkObject* nO);

		private:
			std::map<int, NetworkObject*> m_idToPointer;
			std::map<NetworkObject*, int> m_pointerToId;

			int m_nextNetworkID;

		};
	}
}

