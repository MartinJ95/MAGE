#include "Vector2f.h"



Vector2f::Vector2f()
{
}

Vector2f::Vector2f(float x, float y)
	: x(x),
	y(y)
{
}

Vector2f::Vector2f(const Vector2f& vector)
	: x(vector.x),
	y(vector.y)
{}

float Vector2f::length() const
{
	return sqrt(x * x + y * y);
}

Vector2f Vector2f::normalised() const
{
	float l = length();
	return Vector2f(x / l, y / l);
}

void Vector2f::normaliseInPlace()
{
	float l = length();
	x = x / l;
	y = y / l;
	return;
}


Vector2f::~Vector2f()
{
}
