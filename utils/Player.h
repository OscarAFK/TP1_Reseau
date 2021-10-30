#pragma once
#include "NetworkObject.h"

class Player : public NetworkObject {
public:

	Player(Vector3 position, Vector3 taille, Quaternion rotation, int vie, int armure, float argent, char nom[128]);
	Player();

	void Print();
	void Write(Serializer * s);
	void Read(Deserializer* d);
	static Player* Create() { return new Player(); }

private:
	Vector3 m_position;
	Vector3 m_taille;
	Quaternion m_rotation;
	int m_vie;
	int m_armure;
	float m_argent;
	char m_nom[128];


};