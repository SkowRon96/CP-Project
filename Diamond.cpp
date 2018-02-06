#include "Diamond.h"

using namespace std;

// Methods that enable creating Diamond, drawing it on a screen.

Diamond::Diamond(double xx, double yy) :Object(xx, yy) 
{
	type = Object_Type::diamond;
};

void Diamond::draw()
{

	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 11);
	cout << "*";
}

Diamond::~Diamond()
{
}
