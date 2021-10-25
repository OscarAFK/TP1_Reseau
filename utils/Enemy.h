#pragma once
#include "NetworkObject.h"

enum class typeEnemy : uint8_t
{
	Sbire = 0x00,
	Boss = 0x01,
	typeEnemy_Max,
};

class Enemy : public NetworkObject {
public:

	Enemy(Vector3 position, Quaternion rotation, int vie, typeEnemy tEnemy);

	void Print();
	void Write(Serializer * s);
	void Read(Deserializer* d);

private:
	Vector3 m_position;
	Quaternion m_rotation;
	int m_vie;
	typeEnemy m_tEnemy;
};

