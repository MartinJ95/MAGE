#pragma once
#define _USE_MATH_DEFINES
#include <math.h>


class Vector3f
{
public:
	Vector3f();
	Vector3f(const float x, const float y, const float z);
	Vector3f(const Vector3f& vector);

	float length() const;
	Vector3f normalised() const;
	void normaliseInPlace();
	float dotProduct(const Vector3f& other) const;
	float angleBetween(const Vector3f& other) const;
	Vector3f crossProduct(const Vector3f& other) const;

	Vector3f operator+(const Vector3f& other) const
	{
		return Vector3f(x + other.x, y + other.y, z + other.z);
	}

	Vector3f operator*(const float& scaler) const
	{
		return Vector3f(x * scaler, y * scaler, z * scaler);
	}

	Vector3f operator*(const Vector3f& other) const
	{
		return Vector3f(x * other.x, y*other.y, z * other.y);
	}

	bool operator==(const Vector3f& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const Vector3f& other) const
	{
		return !(*this == other);
	}

	void operator=(const Vector3f& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	float x, y, z;
	~Vector3f();
};

