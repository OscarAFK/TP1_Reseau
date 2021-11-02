#include "Enemy.h"

namespace uqac {
	namespace utilsTP3 {

		Enemy::Enemy(Vector3 position, Quaternion rotation, int vie, typeEnemy tEnemy) :
			m_position(position), m_rotation(rotation), m_vie(vie), m_tEnemy(tEnemy) {}

		Enemy::Enemy() : m_position(Vector3(0, 0, 0)), m_rotation(Quaternion(0, 0, 0, 1)), m_vie(0), m_tEnemy(typeEnemy::Boss){}

		Enemy Enemy::generateRandomEnemy()
		{
			auto randomPos = Vector3(randomInt(-500, 500), randomInt(-500, 500), randomInt(0, 100));
			auto randomRot = Quaternion(0,0,0,1);									//Not random, but working
			return Enemy(randomPos, randomRot, randomInt(0, 1000),typeEnemy(randomInt(0, 2)));
		}

		void Enemy::Print() {
			std::string stringType = m_tEnemy == typeEnemy::Sbire ? "Sbire" : "Boss";
			std::cout << "---Enemy summary---\n\nType: " << stringType
				<< "\nPosition: (" << m_position.x << ", " << m_position.y << ", " << m_position.z << ")\n"
				<< "Rotation: (" << m_rotation.x << ", " << m_rotation.y << ", " << m_rotation.z << ", " << m_rotation.w << ")\n"
				<< "Vie: " << m_vie << std::endl;
		}

		void Enemy::Write(serialization::Serializer* s)
		{

			serialization::Compressor comp;

			serialization::Vector3_32 posComp = comp.compressVector3_32(m_position, -500, 500, -500, 500, 0, 100, 3);
			s->Serialize(posComp.x);
			s->Serialize(posComp.y);
			s->Serialize(posComp.z);

			serialization::Quaternion_16 quatComp = comp.compressQuaternions(m_rotation);
			s->Serialize(quatComp.x);
			s->Serialize(quatComp.y);
			s->Serialize(quatComp.z);

			uint16_t vieComp = comp.compressInt(m_vie, 0, 1000);
			s->Serialize(vieComp);


			//J'ai fait ça sans trop réfléchir, à revoir
			/*uint8_t tEnemyComp = comp.compressInt(static_cast<uint8_t>(m_tEnemy), 0x00, 0x01);
			s->Serialize(tEnemyComp);*/
		}

		void Enemy::Read(serialization::Deserializer* d)
		{
			serialization::Compressor comp;

			uint32_t posXComp = d->Read<uint32_t>();
			uint32_t posYComp = d->Read<uint32_t>();
			uint32_t posZComp = d->Read<uint32_t>();
			serialization::Vector3_32 posComp = serialization::Vector3_32(posXComp, posYComp, posZComp);
			m_position = comp.decompressVector3_32(posComp, -500, 500, -500, 500, 0, 100, 3);

			uint16_t rotXComp = d->Read<uint16_t>();
			uint16_t rotYComp = d->Read<uint16_t>();
			uint16_t rotZComp = d->Read<uint16_t>();
			serialization::Quaternion_16 rotComp = serialization::Quaternion_16(rotXComp, rotYComp, rotZComp);
			m_rotation = comp.decompressQuaternions(rotComp);

			uint16_t vieComp = d->Read<uint16_t>();
			m_vie = comp.decompressInt(vieComp, 0, 1000);
		}
		uint8_t Enemy::GetClassId()
		{
			return Enemy::m_classID;
		}
	}
}