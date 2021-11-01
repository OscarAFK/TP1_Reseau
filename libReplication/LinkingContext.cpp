#include "LinkingContext.h"

namespace uqac {
    namespace replication {

        void LinkingContext::addNetworkObject(NetworkObject* nO)
        {
            m_idToPointer[m_nextNetworkID] = nO;
            m_pointerToId[nO] = m_nextNetworkID;
            m_nextNetworkID++;
        }

        void LinkingContext::removeNetworkObject(NetworkObject* nO)
        {
            int networkId = m_pointerToId[nO];
            m_idToPointer.erase(networkId);
            m_pointerToId.erase(nO);
        }

        std::optional<NetworkObject*> LinkingContext::getNetworkObject(int netId)
        {
            return std::optional<NetworkObject*>(m_idToPointer[netId]);
        }

        std::optional<int> LinkingContext::getNetworkId(NetworkObject* nO)
        {
            return std::optional<int>(m_pointerToId[nO]);
        }
    }
}