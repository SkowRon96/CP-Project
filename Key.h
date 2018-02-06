#pragma once
#ifndef Key_h
#define Key_h

#include"Libraries.h"

using namespace std;

// Header including implementation of the Key class

class Key :public Object
{
public:
	Key(double xx, double yy);
	void draw();
	~Key();
};

#endif