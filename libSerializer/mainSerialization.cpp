#include "Player.h"

void main() {
	
	Player p1 = Player(Vector3(1.0, 2.0, 3.0), Vector3(4.0, 5.0, 6.0), Quaternion(7.0,8.0,9.0,1.0),100,50,420.69,"Charlot");

	p1.Print();

}