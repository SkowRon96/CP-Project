#include "Enemy.h"

// Methods that enable creating Enemy, drawing it on a screen and moving enemies

Enemy::Enemy(double xx, double yy) :Object(xx, yy)
{
	type = Object_Type::enemy;
}

void Enemy::move()
{

}
void Enemy::draw()
{
	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour,5);
	cout << "E";
}
Enemy::~Enemy()
{
}
