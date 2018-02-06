#pragma once
#ifndef Door_h
#define Door_h

#include"Libraries.h"

using namespace std;

// Header including implementation of the Door class

class Door :public Object
{
	bool door_open;
public:
	Door(double xx, double yy);
	void draw();
	bool open_door();

	~Door();
}; 

#endif