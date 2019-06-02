#include "Vector3i.h"

Vector3i::Vector3i()
	: x(0.f),
	y(0.f),
	z(0.f)
{
}

Vector3i::Vector3i(const int x, const int y, const int z)
	: x(x),
	y(y),
	z(z)
{
}

Vector3i::Vector3i(const Vector3i & vector)
	: x(vector.x),
	y(vector.y),
	z(vector.z)
{
}

float Vector3i::length() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3i Vector3i::normalised() const
{
	float l = length();
	return Vector3i(x / l, y / l, z / l);
}

void Vector3i::normaliseInPlace()
{
	float l = length();
	x = x / l;
	y = y / l;
	z = z / l;
	return;
}




Vector3i::~Vector3i()
{
}
