#pragma once
#include "ElEDefines.h"

class ElEVector2f;

class ElEMatrix3x3
{
public:
	ElEfloat arr[9];
	ElEMatrix3x3();
	~ElEMatrix3x3();
	void Translation2D(const ElEfloat& x, const ElEfloat& y);
	void Scale2D(const ElEfloat& x, const ElEfloat& y);
	ElEMatrix3x3& operator+=(const ElEMatrix3x3& rhs);
	ElEMatrix3x3& operator-=(const ElEMatrix3x3& rhs);
	ElEMatrix3x3& operator*=(const ElEMatrix3x3& rhs);
	ElEMatrix3x3& operator/=(const ElEfloat& rhs);
	ElEMatrix3x3& operator/=(const ElEint& rhs);
};

ElEVector2f operator*(const ElEVector2f& lhs, const ElEMatrix3x3& rhs);