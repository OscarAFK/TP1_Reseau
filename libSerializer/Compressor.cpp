#include "Compressor.h"

float Compressor::getRange(float min , float max) {
	if (min > 0) {
		std::cout << "minFloat doit etre inferieur à 1";
		return -1;
	}


	std::cout << "Val min = " << min << std::endl;
	std::cout << "Val max = " << max << std::endl;

	float range = abs(min) + abs(max);
	std::cout << "Range : 0 to  " << range << std::endl;

	return range;
}

//---------------------FLOAT----------------------------

/*uint16_t Compressor::compressFloat(float value, float minFloat, float maxFloat, int precision)
{
	
	std::cout << "Start Float Compression" << std::endl;
	std::cout << "value : " << value << " has size : " << sizeof(value) << std::endl;

	float range =  getRange(minFloat, maxFloat) * pow(10, precision);
	std::cout << "Precision = " << precision << " ----> Range : 0 to " << range << std::endl;

	float valueChange = value + abs(minFloat);	// make the value unsigned
	std::cout << "Val unsigned = " << valueChange << std::endl;

	valueChange = valueChange * pow(10, precision);	// change the precision for the value
	std::cout << "Val unsigned with precision = " << valueChange << std::endl;


	std::cout << "value : " << valueChange << " has size : " << sizeof(valueChange) << std::endl;

	// compression vers uint16_t
	uint16_t comp;
	comp = valueChange;
	
	std::cout << "now value : " << comp << " has size : " << sizeof(comp) << std::endl;
	std::cout << "\n\n";
	return comp;
}*/


float Compressor::decompressFloat(uint32_t value, float minFloat, float maxFloat, int precision)
{
	std::cout << "Start Float Decompression" << std::endl;

	std::cout << "value : " << value << " has size : " << sizeof(value) << std::endl;

	// decompression avec un mutliplicateur de 100
	float decomp = value;
	decomp = decomp / pow(10, precision);
	decomp = decomp - abs(minFloat);

	// Affichage du float sous la forme bit
	std::cout << "now value : " << decomp << " has size : " << sizeof(decomp) <<std::endl;
	std::cout << "\n\n";

	return decomp;
}


//---------------------Int----------------------------
uint16_t Compressor::compressInt(int value, int minInt, int maxInt)
{
	std::cout << "Start int Compression" << std::endl;
	std::cout << "value : " << value << " has size : " << sizeof(value) << std::endl;

	int range = getRange(minInt, maxInt);

	if (value < minInt || value > maxInt)
	{
		std::cout << "Error Value to small or to big" << std::endl;
		return -1;
	}

	std::cout << "Val unsigned = " << value + abs(minInt) << std::endl;

	uint16_t comp = value + abs(minInt);
	std::cout << "now value : " << comp << " has size : " << sizeof(comp) << std::endl;

	std::cout << "\n\n";

	return comp;
}

int Compressor::decompressInt(uint16_t value, int minInt, int maxInt)
{
	std::cout << "Start int DeCompression" << std::endl;

	std::cout << "compress value : " << value << " has size : " << sizeof(value) << std::endl;

	int decomp = value;
	decomp = value - abs(minInt);


	std::cout << "decompressed value : " << decomp << " has size : " << sizeof(decomp) << std::endl;

	std::cout << "\n\n";

	return decomp;
}


//--------------------- Vector3 ----------------------------
Vector3_16 Compressor::compressVector3(Vector3 vector, float minFloatX, float maxFloatX, 
														float minFloatY, float maxFloatY, 
														float minFloatZ, float maxFloatZ, int precision)
{
	std::cout << "---- Start Vector Compression ---- " << std::endl;
	std::cout << "Vector x = " << vector.x << ", y = " << vector.y << ", z = " << vector.z << std::endl;
	return Vector3_16(
		compressFloat<uint16_t>(vector.x, minFloatX, maxFloatX, precision),
		compressFloat<uint16_t>(vector.y, minFloatY, maxFloatY, precision),
		compressFloat<uint16_t>(vector.z, minFloatZ, maxFloatZ, precision)
		);
}

Vector3 Compressor::decompressVector3(Vector3_16 vector, float minFloatX, float maxFloatX,
												float minFloatY, float maxFloatY,
												float minFloatZ, float maxFloatZ, int precision)
{
	std::cout << "---- Start Vector DeCompression ---- " << std::endl;


	Vector3 vectorDecomp = Vector3(
		decompressFloat(vector.x, minFloatX, maxFloatX, precision),
		decompressFloat(vector.y, minFloatY, maxFloatY, precision),
		decompressFloat(vector.z, minFloatZ, maxFloatZ, precision)
	);

	std::cout << "Vector x = " << vectorDecomp.x << ", y = " << vectorDecomp.y << ", z = " << vectorDecomp.z << std::endl;

	return vectorDecomp;
}



//--------------------- Vector3_32 ----------------------------

Vector3_32 Compressor::compressVector3_32(Vector3 vector, float minFloatX, float maxFloatX,
	float minFloatY, float maxFloatY,
	float minFloatZ, float maxFloatZ, int precision)
{
	std::cout << "---- Start Vector Compression ---- " << std::endl;
	std::cout << "Vector x = " << vector.x << ", y = " << vector.y << ", z = " << vector.z << std::endl;
	return Vector3_32(
		compressFloat<uint32_t>(vector.x, minFloatX, maxFloatX, precision),
		compressFloat<uint32_t>(vector.y, minFloatY, maxFloatY, precision),
		compressFloat<uint32_t>(vector.z, minFloatZ, maxFloatZ, precision)
	);
}

Vector3 Compressor::decompressVector3_32(Vector3_32 vector, float minFloatX, float maxFloatX,
	float minFloatY, float maxFloatY,
	float minFloatZ, float maxFloatZ, int precision)
{
	std::cout << "---- Start Vector DeCompression ---- " << std::endl;


	Vector3 vectorDecomp = Vector3(
		decompressFloat(vector.x, minFloatX, maxFloatX, precision),
		decompressFloat(vector.y, minFloatY, maxFloatY, precision),
		decompressFloat(vector.z, minFloatZ, maxFloatZ, precision)
	);

	std::cout << "Vector x = " << vectorDecomp.x << ", y = " << vectorDecomp.y << ", z = " << vectorDecomp.z << std::endl;

	return vectorDecomp;
}



//--------------------- Quaternion ----------------------------

Quaternion_16 Compressor::compressQuaternions(Quaternion quaternion)
{
	std::cout << "---- Start Quaternion Compression ---- " << std::endl;

	// define variable
	float minValue = -1;
	float maxValue = 1;
	float precision = 3;
	
	return Quaternion_16(
		compressFloat<uint16_t>(quaternion.x, minValue, maxValue, precision),
		compressFloat<uint16_t>(quaternion.y, minValue, maxValue, precision),
		compressFloat<uint16_t>(quaternion.z, minValue, maxValue, precision)
	);
}

Quaternion Compressor::decompressQuaternions(Quaternion_16 quaternion)
{
	std::cout << "---- Start Quaternion DeCompression ---- " << std::endl;

	// define variable
	float minValue = -1;
	float maxValue = 1;
	float precision = 3; 

	float _x = decompressFloat(quaternion.x, minValue, maxValue, precision);
	float _y = decompressFloat(quaternion.y, minValue, maxValue, precision);
	float _z = decompressFloat(quaternion.z, minValue, maxValue, precision);

	Quaternion quatDecomp = Quaternion(
		_x,
		_y,
		_z,
		sqrt(1 - (pow(_x, 2) + pow(_y, 2) + pow(_z, 2)))
	);

	std::cout << "("<< quatDecomp.x << "," << quatDecomp.y << "," << quatDecomp.z << "," << quatDecomp.w << ")" << std::endl;

	return quatDecomp;
}