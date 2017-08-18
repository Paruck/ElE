#include "ElEMatrix3x3.h"
#include "ElEVector2f.h"
#include <cmath>


ElEMatrix3x3::ElEMatrix3x3()
{
	for (ElEint i = 9; i--;)
		arr[i] = 0;
	arr[0] = 1;
	arr[4] = 1;
	arr[8] = 1;
}


ElEMatrix3x3::~ElEMatrix3x3()
{
}

void ElEMatrix3x3::Translation2D(const ElEfloat & x, const ElEfloat & y)
{
	arr[2] = x;
	arr[5] = y;
}

void ElEMatrix3x3::Scale2D(const ElEfloat & x, const ElEfloat & y)
{
	arr[0] = x;
	arr[4] = y;
}

void ElEMatrix3x3::Rotation2D(const ElEfloat & ang)
{
	arr[0] = cos(ang*degtorad);
	arr[1] = sin(ang*degtorad);
	arr[3] = 0 - arr[1];
	arr[4] = arr[0];
}

ElEMatrix3x3 & ElEMatrix3x3::operator+=(const ElEMatrix3x3 & rhs)
{
	for (ElEint i = 9; i--;)
		arr[i] += rhs.arr[i];
	return *this;
}

ElEMatrix3x3 & ElEMatrix3x3::operator-=(const ElEMatrix3x3 & rhs)
{
	for (ElEint i = 9; i--;)
		arr[i] -= rhs.arr[i];
	return *this;
}

ElEMatrix3x3 & ElEMatrix3x3::operator*=(const ElEMatrix3x3 & rhs)
{
	arr[0] = (rhs.arr[0] * arr[0]) + (rhs.arr[1] * arr[3]) + (rhs.arr[2] * arr[6]);
	arr[1] = (rhs.arr[0] * arr[1]) + (rhs.arr[1] * arr[4]) + (rhs.arr[2] * arr[7]);
	arr[2] = (rhs.arr[0] * arr[2]) + (rhs.arr[1] * arr[5]) + (rhs.arr[2] * arr[8]);
	arr[3] = (rhs.arr[3] * arr[0]) + (rhs.arr[4] * arr[3]) + (rhs.arr[5] * arr[6]);
	arr[4] = (rhs.arr[3] * arr[1]) + (rhs.arr[4] * arr[4]) + (rhs.arr[5] * arr[7]);
	arr[5] = (rhs.arr[3] * arr[2]) + (rhs.arr[4] * arr[5]) + (rhs.arr[5] * arr[8]);
	arr[6] = (rhs.arr[6] * arr[0]) + (rhs.arr[7] * arr[3]) + (rhs.arr[8] * arr[6]);
	arr[7] = (rhs.arr[6] * arr[1]) + (rhs.arr[7] * arr[4]) + (rhs.arr[8] * arr[7]);
	arr[8] = (rhs.arr[6] * arr[2]) + (rhs.arr[7] * arr[5]) + (rhs.arr[8] * arr[8]);
	return *this;	
}

ElEMatrix3x3 & ElEMatrix3x3::operator/=(const ElEfloat & rhs)
{
	for (ElEint i = 9; i--;)
		arr[i] /= rhs;
	return *this;
}

ElEMatrix3x3 & ElEMatrix3x3::operator/=(const ElEint & rhs)
{
	for (ElEint i = 9; i--;)
		arr[i] /= rhs;
	return *this;
}

ElEVector2f operator*(const ElEVector2f & lhs, const ElEMatrix3x3 & rhs)
{
	return ElEVector2f((lhs.x * rhs.arr[0]) + (lhs.y * rhs.arr[1]) + rhs.arr[2],
		(lhs.x * rhs.arr[3]) + (lhs.y * rhs.arr[4]) + rhs.arr[5]);
}
