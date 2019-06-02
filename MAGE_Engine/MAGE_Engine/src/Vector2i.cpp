#include "Vector2i.h"

Vector2i::Vector2i()
	: x(0),
	y(0)
{
}

Vector2i::Vector2i(const int x, const int y)
	: x(x),
	y(y)
{
}

Vector2i::Vector2i(const Vector2i& vector)
	: x(vector.x),
	y(vector.y)
{}

float Vector2i::length() const
{
	return sqrt(x * x + y * y);
}

Vector2i Vector2i::normalised() const
{
	float l = length();
	return Vector2i(x / l, y / l);
}

void Vector2i::normaliseInPlace()
{
	float l = length();
	x = x / l;
	y = y / l;
	return;
}


Vector2i::~Vector2i()
{
}

