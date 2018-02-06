#include "Key.h"

// Methods that enable creating Key, drawing it on a screen.

Key::Key(double xx, double yy) :Object(xx, yy)
{
	type = Object_Type::key;
};

void Key::draw()
{
	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 13);
	cout << "K";
}

Key::~Key()
{
}
