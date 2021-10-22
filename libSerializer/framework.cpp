#include "framework.h"

void Quaternion::Write(Serializer* s)
{
	s->Serialize(x);
	s->Serialize(y);
	s->Serialize(z);
	s->Serialize(w);
}

void Quaternion::Read(Deserializer* d)
{
	x = d->Read<float>();
	y = d->Read<float>();
	z = d->Read<float>();
	w = d->Read<float>();
}

void Vector3::Write(Serializer* s)
{
	s->Serialize(x);
	s->Serialize(y);
	s->Serialize(z);
}

void Vector3::Read(Deserializer* d)
{
	x = d->Read<float>();
	y = d->Read<float>();
	z = d->Read<float>();
}