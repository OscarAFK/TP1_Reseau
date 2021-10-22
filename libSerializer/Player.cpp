#include "Player.h"


Player::Player(Vector3 position, Vector3 taille, Quaternion rotation, int vie, int armure, float argent, char nom[128]) :
	m_position(position), m_taille(taille), m_rotation(rotation), m_vie(vie), m_armure(armure), m_argent(argent)
{
	std::copy(nom, nom+128, m_nom);
}

void Player::Print() {
	std::cout << "---Player summary---\n\nName: " << m_nom
		<< "\nPosition: (" << m_position.x << ", " << m_position.y << ", " << m_position.z << ")\n"
		<< "Taille: (" << m_taille.x << ", " << m_taille.y << ", " << m_taille.z << ")\n"
		<< "Rotation: (" << m_rotation.x << ", " << m_rotation.y << ", " << m_rotation.z << ", " << m_rotation.w << ")\n"
		<< "Vie: " << m_vie
		<< "\nArmure: " << m_armure
		<< "\nArgent: " << m_argent  << "\n---------------"<< std::endl;
}

void Player::Write(Serializer* s)
{
	m_position.Write(s);
	m_taille.Write(s);
	m_rotation.Write(s);
	s->Serialize(m_vie);
	s->Serialize(m_armure);
	s->Serialize(m_argent);
	//s->Serialize(m_nom, 128);
}

void Player::Read(Deserializer *d)
{
	m_position.Read(d);
	m_taille.Read(d);
	m_rotation.Read(d);
	m_vie = d->Read<int>();
	m_armure = d->Read<int>();
	m_argent = d->Read<float>();
	/*std::vector<char> nom = d->Read(128);
	std::copy(reinterpret_cast<char*>(nom.data()),
		reinterpret_cast<char*>(nom.data()) + nom.size(),
		m_nom);*/
}
