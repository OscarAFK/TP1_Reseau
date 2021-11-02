#include "LinkingContext.h"

namespace uqac {
    namespace replication {
        LinkingContext::LinkingContext() : m_nextNetworkID(0) {}


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
            std::optional<utilsTP3::NetworkObject*> returnValue;
            auto it = m_idToPointer.find(netId);
            if (it != m_idToPointer.end())
                returnValue = m_idToPointer[netId];
            else returnValue = std::nullopt;
            return returnValue;
        }

        std::optional<int> LinkingContext::getNetworkId(utilsTP3::NetworkObject* nO)
        {
            std::optional<int> returnValue;
            auto it = m_pointerToId.find(nO);
            if (it != m_pointerToId.end())
                returnValue = m_pointerToId[nO];
            else returnValue = std::nullopt;
            return returnValue;
        }
    }
}