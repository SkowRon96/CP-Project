#include "Empty space.h"

using namespace std;

// Methods that enable creating Empty space, drawing it on a screen.

Empty_space::Empty_space(double xx, double yy) :Object(xx, yy) 
{
	type = Object_Type::empty_space;
};

void Empty_space::draw()
{
	cout << " ";
	
}
Empty_space::~Empty_space()
{
}
