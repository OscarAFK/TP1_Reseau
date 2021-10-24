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
	Compressor comp;

	Vector3_32 posComp = comp.compressVector3_32(m_position, -500, 500, -500,500,0,100 , 3);
	s->Serialize(posComp.x);
	s->Serialize(posComp.y);
	s->Serialize(posComp.z);
	
	Vector3_32 tailleComp = comp.compressVector3_32(m_taille, -500, 500, -500, 500, 0, 100, 3);
	s->Serialize(tailleComp.x);
	s->Serialize(tailleComp.y);
	s->Serialize(tailleComp.z);

	Quaternion_16 quatComp = comp.compressQuaternions(m_rotation);
	s->Serialize(quatComp.x);
	s->Serialize(quatComp.y);
	s->Serialize(quatComp.z);

	uint16_t vieComp = comp.compressInt(m_vie, 0, 300);
	uint16_t armureComp = comp.compressInt(m_armure, 0, 50);
	uint32_t argentComp = comp.compressFloat<uint32_t>(m_argent, -99999, 99999, 3);
	s->Serialize(vieComp);
	s->Serialize(armureComp);
	s->Serialize(argentComp);
	//s->Serialize(m_nom, 128);
}

void Player::Read(Deserializer *d)
{
	Compressor comp;

	
	uint32_t posXComp = d->Read<uint32_t>();
	uint32_t posYComp = d->Read<uint32_t>();
	uint32_t posZComp = d->Read<uint32_t>();
	Vector3_32 posComp = Vector3_32(posXComp, posYComp, posZComp);
	m_position = comp.decompressVector3_32(posComp, -500, 500, -500, 500, 0, 100, 3);
	
	uint32_t tailleXComp = d->Read<uint32_t>();
	uint32_t tailleYComp = d->Read<uint32_t>();
	uint32_t tailleZComp = d->Read<uint32_t>();
	Vector3_32 tailleComp = Vector3_32(tailleXComp, tailleYComp, tailleZComp);
	m_taille = comp.decompressVector3_32(tailleComp, -500, 500, -500, 500, 0, 100, 3);

	uint16_t rotXComp = d->Read<uint16_t>();
	uint16_t rotYComp = d->Read<uint16_t>();
	uint16_t rotZComp = d->Read<uint16_t>();
	Quaternion_16 rotComp = Quaternion_16(rotXComp, rotYComp, rotZComp);
	m_rotation = comp.decompressQuaternions(rotComp);


	uint16_t vieComp = d->Read<uint16_t>();
	m_vie = comp.decompressInt(vieComp, 0, 300);

	uint16_t armureComp = d->Read<uint16_t>();
	m_armure = comp.decompressInt(armureComp, 0, 50);

	uint32_t argentComp = d->Read<uint32_t>();
	m_argent = comp.decompressFloat(argentComp, -99999, 99999,3);
	
	/*std::vector<char> nom = d->Read(128);
	std::copy(reinterpret_cast<char*>(nom.data()),
		reinterpret_cast<char*>(nom.data()) + nom.size(),
		m_nom);*/
}
