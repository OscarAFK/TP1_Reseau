#include "framework.h"
#include <algorithm>
#include <iostream>

class Player {
public:

	Player(Vector3 position, Vector3 taille, Quaternion rotation, int vie, int armure, float argent, char nom[128]);

	void Print();
	void Write();
	void Read();

private:
	Vector3 m_position;
	Vector3 m_taille;
	Quaternion m_rotation;
	int m_vie;
	int m_armure;
	float m_argent;
	char m_nom[128];


};