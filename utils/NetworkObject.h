#pragma once
#include <frameworkTP3.h>
#include <iostream>
#include <Serializer.h>
#include <Deserializer.h>

namespace uqac {
	namespace utilsTP3 {
		using namespace utils;

		class NetworkObject {
		public:

			NetworkObject() = default;
			~NetworkObject() = default;

			virtual void Print() = 0;
			virtual void Write(serialization::Serializer* s) = 0;
			virtual void Read(serialization::Deserializer* d) = 0;
			virtual uint8_t GetClassId() = 0;
		};
	}
}