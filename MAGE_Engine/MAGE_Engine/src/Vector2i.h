#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Vector2i
{
public:
	Vector2i();
	Vector2i(const int x, const int y);
	Vector2i(const Vector2i& vector);

	float length() const;
	Vector2i normalised() const;
	void normaliseInPlace();
	float dotProduct(const Vector2i& other) const;
	float angleBetween(const Vector2i& other) const;

	Vector2i operator+(const Vector2i& other) const
	{
		return Vector2i(x + other.x, y + other.y);
	}

	Vector2i operator*(const int& scaler) const
	{
		return Vector2i(x * scaler, y * scaler);
	}

	Vector2i operator*(const Vector2i& other) const
	{
		return Vector2i(x * other.x, y*other.y);
	}

	bool operator==(const Vector2i& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2i& other) const
	{
		return !(*this == other);
	}

	void operator=(const Vector2i& other)
	{
		x = other.x;
		y = other.y;
	}

	int x, y;
	~Vector2i();
};