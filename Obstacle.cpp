#include "Obstacle.h"

using namespace std;

// Methods that enable creating Obstacle, drawing it on a screen.

Obstacle::Obstacle(double xx, double yy) :Object(xx, yy) 
{
	type = Object_Type::obstacle;
	is_moved = false;
};


void Obstacle::draw()
{
	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 7);
	cout << "O";
}

Obstacle::~Obstacle()
{
}