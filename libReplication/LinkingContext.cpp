#include "LinkingContext.h"

namespace uqac {
    namespace replication {

        void LinkingContext::addNetworkObject(utilsTP3::NetworkObject* nO)
        {
            m_idToPointer[m_nextNetworkID] = nO;
            m_pointerToId[nO] = m_nextNetworkID;
            m_nextNetworkID++;
        }

        void LinkingContext::removeNetworkObject(utilsTP3::NetworkObject* nO)
        {
            int networkId = m_pointerToId[nO];
            m_idToPointer.erase(networkId);
            m_pointerToId.erase(nO);
        }

        std::optional<utilsTP3::NetworkObject*> LinkingContext::getNetworkObject(int netId)
        {
            return std::optional<utilsTP3::NetworkObject*>(m_idToPointer[netId]);
        }

        std::optional<int> LinkingContext::getNetworkId(utilsTP3::NetworkObject* nO)
        {
            return std::optional<int>(m_pointerToId[nO]);
        }
    }
}