#pragma once
#include <cstdint>
#include <stdlib.h>     /* srand, rand */

namespace uqac {
	namespace utils {

		enum class ClassID : uint8_t
		{
			Player = 0x00,
			Enemy = 0x01,
			ClassID_Max
		};

		int randomInt(int min, int max);
	}
}