#pragma once
#ifndef Wall_h
#define Wall_h

#include"Libraries.h"

using namespace std;

// Header including implementation of the Wall class

class Wall :public Object
{
public:
	Wall(double xx, double yy);
	void draw();
	~Wall();
};

#endif