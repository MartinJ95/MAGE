#pragma once
#include "Vector3f.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Matrix4f
{
public:
	Matrix4f();
	Matrix4f(const float x, const float y, const float z, const float w);
	Matrix4f(const Vector3f v, const float w);
	Matrix4f(const Matrix4f& m);
	Matrix4f(const float x1, const float y1, const float z1, const float w1,
		const float x2, const float y2, const float z2, const float w2,
		const float x3, const float y3, const float z3, const float w3,
		const float x4, const float y4, const float z4, const float w4);

	void translate(const Vector3f& translation);
	void scale(const Vector3f& scale);
	void rotate(const Vector3f& axisRotation, float angleDegrees);

	void operator=(const Matrix4f& other)
	{
		for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
		{
			values[i][j] = other.values[i][j];
		}
	};

	Matrix4f operator*(const Matrix4f& other)
	{
		return Matrix4f{
			values[1][1] * other.values[1][1] + values[1][2] * other.values[2][1] + values[1][3] * other.values[3][1] + values[1][4] * other.values[4][1],
			values[1][1] * other.values[1][2] + values[1][2] * other.values[2][2] + values[1][3] * other.values[3][2] + values[1][4] * other.values[4][2],
			values[1][1] * other.values[1][3] + values[1][2] * other.values[2][3] + values[1][3] * other.values[3][3] + values[1][4] * other.values[4][3],
			values[1][1] * other.values[1][4] + values[1][2] * other.values[2][4] + values[1][3] * other.values[3][4] + values[1][4] * other.values[4][4],

			values[2][1] * other.values[2][1] + values[2][2] * other.values[2][1] + values[2][3] * other.values[3][1] + values[2][4] * other.values[4][1],
			values[2][1] * other.values[2][2] + values[2][2] * other.values[2][2] + values[2][3] * other.values[3][2] + values[2][4] * other.values[4][2],
			values[2][1] * other.values[2][3] + values[2][2] * other.values[2][3] + values[2][3] * other.values[3][3] + values[2][4] * other.values[4][3],
			values[2][1] * other.values[2][4] + values[2][2] * other.values[2][4] + values[2][3] * other.values[3][4] + values[2][4] * other.values[4][4],

			values[3][1] * other.values[1][1] + values[3][2] * other.values[2][1] + values[3][3] * other.values[3][1] + values[3][4] * other.values[4][1],
			values[3][1] * other.values[1][2] + values[3][2] * other.values[2][2] + values[3][3] * other.values[3][2] + values[3][4] * other.values[4][2],
			values[3][1] * other.values[1][3] + values[3][2] * other.values[2][3] + values[3][3] * other.values[3][3] + values[3][4] * other.values[4][3],
			values[3][1] * other.values[1][4] + values[3][2] * other.values[2][4] + values[3][3] * other.values[3][4] + values[3][4] * other.values[4][4],

			values[4][1] * other.values[1][1] + values[4][2] * other.values[2][1] + values[4][3] * other.values[3][1] + values[4][4] * other.values[4][1],
			values[4][1] * other.values[1][2] + values[4][2] * other.values[2][2] + values[4][3] * other.values[3][2] + values[4][4] * other.values[4][2],
			values[4][1] * other.values[1][3] + values[4][2] * other.values[2][3] + values[4][3] * other.values[3][3] + values[4][4] * other.values[4][3],
			values[4][1] * other.values[1][4] + values[4][2] * other.values[2][4] + values[4][3] * other.values[3][4] + values[4][4] * other.values[4][4],
		};
	}

	float values[4][4];
	~Matrix4f();
};

