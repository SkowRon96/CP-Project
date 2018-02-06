#include "Door.h"

using namespace std;

// Methods that enable creating Door, drawing it on a screen.

Door::Door(double xx, double yy) :Object(xx, yy) 
{
	type = Object_Type::door;
	//door_open = false;
};

void Door::draw()
{
	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 10);
	cout << "D";
	
}
bool Door::open_door()// Method that changes status of the door
{
	return door_open = true;
}
Door::~Door()
{
}
