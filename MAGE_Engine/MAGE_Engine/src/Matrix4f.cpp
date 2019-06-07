#include "Matrix4f.h"

Matrix4f::Matrix4f() 
	: values{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
}
{
}

Matrix4f::Matrix4f(const float x, const float y, const float z, const float w)
	: values{
	x, 0, 0, 0,
	0, y, 0, 0,
	0, 0, z, 0,
	0, 0, 0, 1
}
{
}

Matrix4f::Matrix4f(const Vector3f v, const float w)
	: values{
	v.x, 0, 0, 0,
	0, v.y, 0, 0,
	0, 0, v.z, 0,
	0, 0, 0, 1
}
{
}

Matrix4f::Matrix4f(const float x1, const float y1, const float z1, const float w1,
	const float x2, const float y2, const float z2, const float w2,
	const float x3, const float y3, const float z3, const float w3,
	const float x4, const float y4, const float z4, const float w4)
	: values{
	x1, y1, z1, w1,
	x2, y2, z2, w2,
	x3, y3, z3, w3,
	x4, y4, z4, w4
}
{
}

void Matrix4f::translate(const Vector3f & translation)
{
	*this = *this * Matrix4f(1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1);
}

void Matrix4f::scale(const Vector3f & scale)
{
	*this = *this * Matrix4f(scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1);
}

void Matrix4f::rotate(const Vector3f & axisRotation, float angleDegrees)
{
	if (axisRotation == Vector3f(0, 1, 0))
	{
		*this = *this * Matrix4f((float)cos(angleDegrees), 0, (float)sin(angleDegrees), 0,
			0, 1, 0, 0,
			(float)-sin(angleDegrees), 0, (float)cos(angleDegrees), 0,
			0, 0, 0, 1);
	}
	else if (axisRotation == Vector3f(0, 0, 1))
	{
		*this = *this * Matrix4f((float)cos(angleDegrees), (float)-sin(angleDegrees), 0, 0,
			(float)sin(angleDegrees), (float)cos(angleDegrees), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}
	else if (axisRotation == Vector3f(1, 0, 0))
	{
		*this = *this * Matrix4f(1, 0, 0, 0,
			0, (float)cos(angleDegrees), (float)-sin(angleDegrees), 0,
			0, (float)sin(angleDegrees), (float)cos(angleDegrees), 0,
			0, 0, 0, 1);
	}
}

Matrix4f::Matrix4f(const Matrix4f& m)
{
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)
	{
		values[i][j] = m.values[i][j];
	}
}

Matrix4f::~Matrix4f()
{
}
