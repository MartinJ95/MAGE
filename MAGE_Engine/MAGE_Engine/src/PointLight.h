#pragma once
#include "Component.h"
#include "Maths.h"
class PointLight :
	public Component
{
public:
	PointLight(Entity &entity);
	Vector3f m_intensity;
	Vector3f m_position;
	float m_radius;
	~PointLight();
};

