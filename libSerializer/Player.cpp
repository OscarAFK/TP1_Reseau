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