#pragma once
#ifndef Enemy_h
#define Enemy_h

#include"Libraries.h"

using namespace std;

// Header including implementation of the Enemy class

class Enemy :public Object
{
public:
	Enemy(double xx, double yy);

	void draw();
	void move();
	~Enemy();
};

#endif
