#include "Vector3f.h"

Vector3f::Vector3f()
	: x(0.f),
	y(0.f),
	z(0.f)
{
}

Vector3f::Vector3f(const float x, const float y, const float z)
	: x(x),
	y(y),
	z(z)
{
}

Vector3f::Vector3f(const Vector3f & vector)
	: x(vector.x),
	y(vector.y),
	z(vector.z)
{
}

float Vector3f::length() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3f Vector3f::normalised() const
{
	float l = length();
	return Vector3f(x / l, y / l, z / l);
}

void Vector3f::normaliseInPlace()
{
	float l = length();
	x = x / l;
	y = y / l;
	z = z / l;
	return;
}




Vector3f::~Vector3f()
{
}
