#include "Player.h"
#include <vector>
#include "Serializer.h"
#include <iostream>
#include "Deserializer.h"

void main() {
	
	Player p1 = Player(Vector3(1.0, 2.0, 3.0), Vector3(4.0, 5.0, 6.0), Quaternion(7.0,8.0,9.0,1.0),100,50,420.69,"Charlot");
	Serializer s = Serializer();

	p1.Print();
	
	std::cout << "Writing" << std::endl;
	p1.Write(&s);
	
	std::cout << "Reading" << std::endl;
	std::vector<char> * buffer = s.getContainer();
	Deserializer d = Deserializer(buffer, buffer->size());
	p1.Read(&d);
	
	std::cout << "OK" << std::endl;

	p1.Print();
}