#pragma once
#ifndef Player_h
#define Player_h

#include"Libraries.h"

using namespace std;

// Header including implementation of the Player class

class Player :public Object
{
protected:
	int diamonds;// Number of diamonds
	int keys;// Number of keys
	bool is_killed;// Life status
public:
	Player(double xx, double yy, int d);
	void draw();
	int diamonds_number();
	int keys_number();
	void keys_reduce();
	void collecting(Object_Type t);
	void move(char direction);
	~Player();

};

#endif