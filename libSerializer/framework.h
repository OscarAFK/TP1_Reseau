#pragma once
#include <cstdint>

enum class PlateformEndianess {
	BigEndian,
	LittleEndian
};

constexpr PlateformEndianess DetectEndianess() {
	union {
		uint32_t i;
		char c[4];
	} testEndian = {0x01020304};

	return (testEndian.c[0] == 1) ? PlateformEndianess::BigEndian : PlateformEndianess::LittleEndian;
}

template <typename T>
void SwaptEndian(T& val) {
	union U {
		T val;
		std::array<std::uint8_t, sizeof(T)> raw;
	} src, dst;

	src.val = val;
	std::reverse_copy(src.raw.begin(), src.raw.end(),dst.raw.begin());
	val = dst.val;
}

struct Quaternion {
	float x, y, z, w;

	Quaternion(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};

struct Vector3 {
	float x, y, z;

	Vector3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};