#include "Wall.h"

using namespace std;

// Methods that enable creating Wall, drawing it on a screen.

Wall::Wall(double xx, double yy) :Object(xx, yy) 
{
	type = Object_Type::wall;
};

void Wall::draw()
{
	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 4);
	cout << "#";
}
Wall::~Wall()
{
}
