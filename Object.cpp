#include "Object.h"

using namespace std;

// Methods that enable creating Object, drawing it on a screen and moving it.

Object::Object(double xx, double yy)
{
	x = xx;
	y = yy;
	enemy_go_up = false;
	enemy_go_left = false;
	enemy_go_down = true;
	enemy_go_right = false;
}
void Object::draw()
{
}
void Object::move(Direction d)
{
	switch (d)
	{
	case Down: x = x + 1; break;
	case Up: x = x - 1; break;
	case Left: y = y - 1; break;
	case Right: y = y + 1; break;
	}
}
bool Object::open()
{
	return false;
}

Object::~Object()
{
}
