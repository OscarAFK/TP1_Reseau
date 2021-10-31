#include "NetworkObject.h"

void NetworkObject::Write(Serializer* s)
{
	uint8_t classId = (uint8_t)m_classID;
	s->Serialize(classId);
}

void NetworkObject::Read(Deserializer* d)
{
	m_classID = ClassID(d->Read<uint8_t>());
}
