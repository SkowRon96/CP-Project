#include "Player.h"

using namespace std;

// Methods that enable creating Player, drawing it on a screen.

Player::Player(double xx, double yy, int d) :Object(xx, yy) 
{
	type = Object_Type::player;
	diamonds = d;
	keys = 0;
};

void Player::draw()
{
	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 9);
	cout << "P";
}
int Player::diamonds_number()// Methods showing number of diamonds need to collect
{
	if (diamonds >= 0) cout << "Diamonds to collect: " << diamonds<<"   "<<endl;
	else cout << "                                                                 "<<endl;
	return diamonds;
}
int Player::keys_number()// Methods showing number of keys
{
	cout << "Keys: " << keys << endl;
	return keys;
}
void Player::keys_reduce()// Methods reducing number of keys
{
	keys = keys - 1;
}
void Player::collecting(Object_Type t)// Methods that enable to collect diamonds and keys
{
	if(t==diamond) diamonds = diamonds - 1;
	if(t==key) keys = keys + 1;
}
void Player::move(char direction)// Methods that enable moving player
{
	switch (direction)
	{
	case 80: x = x + 1; break;
	case 72: x = x - 1; break;
	case 75: y = y - 1; break;
	case 77: y = y + 1; break;
	}
}
Player::~Player()
{
}
