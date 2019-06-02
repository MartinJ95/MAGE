#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Vector3i
{
public:
	Vector3i();
	Vector3i(const int x, const int y, const int z);
	Vector3i(const Vector3i& vector);

	float length() const;
	Vector3i normalised() const;
	void normaliseInPlace();
	float dotProduct(const Vector3i& other) const;
	float angleBetween(const Vector3i& other) const;
	Vector3i crossProduct(const Vector3i& other) const;

	Vector3i operator+(const Vector3i& other) const
	{
		return Vector3i(x + other.x, y + other.y, z + other.z);
	}

	Vector3i operator*(const int& scaler) const
	{
		return Vector3i(x * scaler, y * scaler, z * scaler);
	}

	Vector3i operator*(const Vector3i& other) const
	{
		return Vector3i(x * other.x, y*other.y, z * other.y);
	}

	bool operator==(const Vector3i& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const Vector3i& other) const
	{
		return !(*this == other);
	}

	void operator=(const Vector3i& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	int x, y, z;
	~Vector3i();
};

