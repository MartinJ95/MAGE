#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Vector2f
{
public:
	Vector2f();
	Vector2f(const float x, const float y);
	Vector2f(const Vector2f& vector);

	float length() const;
	Vector2f normalised() const;
	void normaliseInPlace();
	float dotProduct(const Vector2f& other) const;
	float angleBetween(const Vector2f& other) const;

	Vector2f operator+(const Vector2f& other) const
	{
		return Vector2f(x + other.x, y + other.y);
	}

	Vector2f operator-(const Vector2f& other) const
	{
		return Vector2f(x - other.x, y - other.y);
	}

	Vector2f operator*(const float& scaler) const
	{
		return Vector2f(x * scaler, y * scaler);
	}

	Vector2f operator*(const Vector2f& other) const
	{
		return Vector2f(x * other.x, y*other.y);
	}

	bool operator==(const Vector2f& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2f& other) const
	{
		return !(*this == other);
	}

	void operator=(const Vector2f& other)
	{
		x = other.x;
		y = other.y;
	}

	float x, y;
	~Vector2f();
};
