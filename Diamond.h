#pragma once
#ifndef Diamond_h
#define Diamond_h

#include"Libraries.h"

using namespace std;

// Header including implementation of the Diamond class

class Diamond :public Object
{
public:
	Diamond(double xx, double yy);
	void draw();
	~Diamond();
};

#endif