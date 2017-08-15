#pragma once
#include "ElEDefines.h"

class ElEVector2f
{
public:
	ElEfloat	x,
				y;
	ElEVector2f() : x(0), y(0) {}

	ElEVector2f(const ElEfloat& _x, const ElEfloat& _y) : x(_x), y(_y) {}
	~ElEVector2f() {}
};

