#pragma once
#ifndef Obstacle_h
#define Obstacle_h
#include"Libraries.h"

using namespace std;

// Header including implementation of the Obstacle class

class Obstacle :public Object
{
public:
	Obstacle(double xx, double yy);
	void draw();
	~Obstacle();
};

#endif