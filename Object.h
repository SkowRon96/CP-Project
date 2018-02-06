#pragma once
#ifndef Object_h
#define Object_h
#include"Libraries.h"

using namespace std;

// Implementation of the main class Object

enum Object_Type// It consists of the type of objects that helps to discriminate objects in vector
{
	player,
	obstacle,
	diamond,
	empty_space, 
	ground,
	wall,
	door, 
	enemy, 
	key
};
enum Direction// It consists of the type of directions 
{
	Right, 
	Left, 
	Down,
	Up
};


class Object
{
	int counter;
	

public:
	double x;// X coordinate
	double y;// Y coordinate
	Object_Type type;// Type of object
	bool is_moved;// Status of object
	bool enemy_go_up;// Statues in which direction enemy should go
	bool enemy_go_left;
	bool enemy_go_down;
	bool enemy_go_right;
	HANDLE colour;

	Object(double xx, double yy);
	virtual void draw();
	virtual void move(Direction);
	virtual bool open();
	~Object();
};
#endif