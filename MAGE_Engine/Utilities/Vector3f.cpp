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

float Vector3f::dotProduct(const Vector3f& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Vector3f::angleBetween(const Vector3f & other) const
{
	return (acos(dotProduct(other) / (length() * other.length())) * 180/M_PI);
}

Vector3f Vector3f::crossProduct(const Vector3f & other) const
{
	return Vector3f(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Vector3f Vector3f::reflect(const Vector3f & normal) const
{
	return *this - (normal * dotProduct(normal)) * 2;
}

Vector3f::~Vector3f()
{
}
