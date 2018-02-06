#include "Ground.h"

using namespace std;

// Methods that enable creating Ground, drawing it on a screen.

Ground::Ground(double xx, double yy) :Object(xx, yy) 
{
	type = Object_Type::ground;
};

void Ground::draw()
{
	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 14);
	cout << "-";
}
Ground::~Ground()
{
}
