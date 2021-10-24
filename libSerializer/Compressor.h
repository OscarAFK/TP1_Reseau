#pragma once
/* Il faut compresser :
 *		Integer
 *		Float
 *		Vector3
 *		Quaternion
 */

/* 
 * uint8_t		0 -> 255					1 byte		8  bits 
 * uint16_t		0 -> 65 535					2 bytes		16 bits
 *
 * int			-2147483648 -> 2147483647	4 bytes		32 bits
 */
#include <iostream>
#include <bitset>
#include "framework.h"

struct Vector3_16 {
	uint16_t x, y, z;

	Vector3_16(uint16_t _x, uint16_t _y, uint16_t _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

struct Vector3_32 {
	uint32_t x, y, z;

	Vector3_32(uint32_t _x, uint32_t _y, uint32_t _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

struct Quaternion_16 {
	uint16_t x, y, z;

	Quaternion_16(uint16_t _x, uint16_t _y, uint16_t _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

class Compressor
{
private :

	float getRange(float min, float max);

public : 

	template <typename T, std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<T>>>* = nullptr>
	T compressFloat(float value, float minFloat, float maxFloat, int precision) {
		std::cout << "Start Float Compression" << std::endl;
		std::cout << "value : " << value << " has size : " << sizeof(value) << std::endl;

		float range = getRange(minFloat, maxFloat) * pow(10, precision);
		std::cout << "Precision = " << precision << " ----> Range : 0 to " << range << std::endl;

		float valueChange = value + abs(minFloat);	// make the value unsigned
		std::cout << "Val unsigned = " << valueChange << std::endl;

		valueChange = valueChange * pow(10, precision);	// change the precision for the value
		std::cout << "Val unsigned with precision = " << valueChange << std::endl;


		std::cout << "value : " << valueChange << " has size : " << sizeof(valueChange) << std::endl;

		// compression vers uint16_t
		T comp;
		comp = valueChange;

		std::cout << "now value : " << comp << " has size : " << sizeof(comp) << std::endl;
		std::cout << "\n\n";
		return comp;
	}


	//uint16_t compressFloat(float value, float minFloat, float maxFloat, int precision);
	float decompressFloat(uint32_t value, float minFloat, float maxFloat, int precision);



	uint16_t compressInt(int value, int minInt, int maxInt);
	int decompressInt(uint16_t value, int minInt, int maxInt);

	Vector3_16 compressVector3(Vector3 vector, float minFloatX, float maxFloatX,
												float minFloatY, float maxFloatY,
												float minFloatZ, float maxFloatZ, int precision);
	Vector3 decompressVector3(Vector3_16 vector, float minFloat, float maxFloat, 
													float minFloatY, float maxFloatY,
													float minFloatZ, float maxFloatZ, int precision);

	Vector3_32 compressVector3_32(Vector3 vector, float minFloatX, float maxFloatX,
		float minFloatY, float maxFloatY,
		float minFloatZ, float maxFloatZ, int precision);
	Vector3 decompressVector3_32(Vector3_32 vector, float minFloat, float maxFloat,
		float minFloatY, float maxFloatY,
		float minFloatZ, float maxFloatZ, int precision);

	Quaternion_16 compressQuaternions(Quaternion quaternion);
	Quaternion decompressQuaternions(Quaternion_16 quaternion);

};

