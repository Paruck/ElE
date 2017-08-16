#include "ElEVector2f.h"

ElEVector2f & ElEVector2f::operator+=(const ElEVector2f & rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

ElEVector2f & ElEVector2f::operator-=(const ElEVector2f & rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

ElEVector2f & ElEVector2f::operator/=(const ElEfloat & rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

ElEVector2f & ElEVector2f::operator/=(const ElEint & rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

ElEVector2f operator+(const ElEVector2f & lhs, const ElEVector2f & rhs)
{
	return ElEVector2f(lhs.x + rhs.x, lhs.y + rhs.y);
}

ElEVector2f operator-(const ElEVector2f & lhs, const ElEVector2f & rhs)
{
	return ElEVector2f(lhs.x - rhs.x, lhs.y - rhs.y);
}

ElEVector2f operator/(const ElEVector2f & lhs, const ElEfloat & rhs)
{
	return ElEVector2f(lhs.x / rhs, lhs.y / rhs);
}

ElEVector2f operator/(const ElEVector2f & lhs, const ElEint & rhs)
{
	return ElEVector2f(lhs.x / rhs, lhs.y / rhs);
}
