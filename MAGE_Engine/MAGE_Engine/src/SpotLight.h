#pragma once
#include "Component.h"
#include "Maths.h"

class SpotLight :
	public Component
{
public:
	SpotLight(Entity &entity);
	Vector3f m_intensity;
	Vector3f m_position;
	float m_fieldOfView;
	float m_range;
	~SpotLight();
};

