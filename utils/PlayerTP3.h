#pragma once
#include <NetworkObject.h>

namespace uqac {
	namespace utilsTP3 {
		using namespace utils;
		class Player : public NetworkObject {
		public:

			enum { m_classID = ClassID::Player };

			Player(Vector3 position, Vector3 taille, Quaternion rotation, int vie, int armure, float argent, char nom[128]);
			Player();

			void Print();
			void Write(serialization::Serializer* s);
			void Read(serialization::Deserializer* d);
			uint8_t GetClassId();
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
	}
}