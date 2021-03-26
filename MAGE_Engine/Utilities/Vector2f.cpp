#include "Vector2f.h"

Vector2f::Vector2f()
	: x(0),
	y(0)
{
}

Vector2f::Vector2f(const float x, const float y)
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

float Vector2f::dotProduct(const Vector2f& other) const
{
	return x * other.x + y * other.y;
}

float Vector2f::angleBetween(const Vector2f & other) const
{
	return (acos(dotProduct(other) / (length() * other.length())) * 180 / M_PI);
}

Vector2f::~Vector2f()
{
}
