#pragma once
#ifndef Emptyspace_h
#define Emptyspace_h

#include"Libraries.h"

using namespace std;

// Header including implementation of the Empty space class

class Empty_space :public Object
{
public:
	Empty_space(double xx, double yy);
	void draw();
	~Empty_space();
};

#endif
