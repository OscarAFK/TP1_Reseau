#include "NetworkObject.h"

namespace uqac {
	namespace utilsTP3 {

		void NetworkObject::Write(serialization::Serializer* s)
		{
			uint8_t classId = (uint8_t)m_classID;
			s->Serialize(classId);
		}

		void NetworkObject::Read(serialization::Deserializer* d)
		{
			m_classID = ClassID(d->Read<uint8_t>());
		}
	}
}