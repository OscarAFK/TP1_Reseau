#include "Compressor.h"

void Compressor::showFloatToBinary(float f)
{
	char* bits = reinterpret_cast<char*>(&f);
	for (std::size_t n = 0; n < sizeof f; ++n)
		std::cout << std::bitset<8>(bits[n]);
	std::cout << '\n';
}



uint16_t Compressor::compressFloat(float value)
{
	// Affichage du float sous la forme bit
	std::cout << "value : " << value << " has size : " << sizeof(value) << "octets,  In Bit --> ";
	showFloatToBinary(value);

	// compression avec un mutliplicateur de 100
	uint16_t comp;
	comp = value * 100;
	
	// affichage de la compression sous la forme bit
	std::bitset<16> y(comp);
	std::cout << "now value : " << comp << " has size : " << sizeof(comp) << "octets, In Bit --> " << y << std::endl;
	return comp;
}

float Compressor::decompressFloat(uint16_t value)
{
	// affichage de la compression sous la forme bit
	std::bitset<16> y(value);
	std::cout << "value : " << value << " has size : " << sizeof(value) << "octets,  In Bit --> " << y << std::endl;

	// decompression avec un mutliplicateur de 100
	float decomp = value;
	decomp = decomp / 100;

	// Affichage du float sous la forme bit
	std::cout << "now value : " << decomp << " has size : " << sizeof(decomp) << "octets, In Bit --> ";
	showFloatToBinary(decomp);

	return decomp;
}

uint16_t Compressor::compressInt(int value, int minInt, int maxInt)
{
	std::cout << "value : " << value << " has size : " << sizeof(value) << std::endl;

	int champsInt = abs(maxInt) + abs(minInt);
	std::cout << "le champs de Int va de 0 a " << champsInt << std::endl;

	if (value < minInt || value > maxInt)
	{
		std::cout << "Error Value to small or to big" << std::endl;
		return -1;
	}

	std::cout << "en forcant le positif, la valeur devient " << value + abs(minInt) << std::endl;

	uint16_t comp = value + abs(minInt);
	std::bitset<16> y(comp);
	std::cout << "now value : " << comp << " has size : " << sizeof(comp) << "octets, In Bit --> " << y << std::endl;


	return comp;
}

int Compressor::decompressInt(uint16_t value, int minInt, int maxInt)
{

	std::bitset<16> y(value);
	std::cout << "compress value : " << value << " has size : " << sizeof(value) << "octets, In Bit --> " << y << std::endl;

	int decomp = value;
	decomp = value - abs(minInt);


	std::cout << "decompressed value : " << decomp << " has size : " << sizeof(decomp) << std::endl;


	return decomp;
}
