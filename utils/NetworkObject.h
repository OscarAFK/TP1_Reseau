#pragma once
#include <frameworkTP3.h>
#include <iostream>
#include <Serializer.h>
#include <Deserializer.h>

namespace uqac {
	namespace replication {

		class NetworkObject {
		public:

			NetworkObject(ClassID classID) : m_classID(classID) {};
			NetworkObject() = default;
			~NetworkObject() = default;

			virtual void Print() = 0;
			virtual void Write(serialization::Serializer* s);
			virtual void Read(serialization::Deserializer* d);

			ClassID m_classID;
		};
	}
}