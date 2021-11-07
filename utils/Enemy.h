#pragma once
#include <NetworkObject.h>

namespace uqac {
	namespace utilsTP3 {
		using namespace utils;

		enum class typeEnemy : uint8_t
		{
			Sbire = 0x00,
			Boss = 0x01,
			typeEnemy_Max,
		};

		class Enemy : public NetworkObject {
		public:

			enum { m_classID = ClassID::Enemy };

			Enemy(Vector3 position, Quaternion rotation, int vie, typeEnemy tEnemy);
			Enemy();

			static Enemy generateRandomEnemy();

			void Print();
			void Write(serialization::Serializer* s);
			void Read(serialization::Deserializer* d);
			uint8_t GetClassId();
			static Enemy* Create() { return new Enemy(); }

		private:
			Vector3 m_position;
			Quaternion m_rotation;
			int m_vie;
			typeEnemy m_tEnemy;
		};

	}
}