#pragma once
#ifndef Ground_h
#define Ground_h

#include"Libraries.h"

using namespace std;

// Header including implementation of the Ground class

class Ground:public Object
{
public:
	Ground(double xx, double yy);
	void draw();
	~Ground();
};

#endif
