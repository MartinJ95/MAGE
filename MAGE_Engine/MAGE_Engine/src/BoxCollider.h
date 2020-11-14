#pragma once
#include "Component.h"
#include "Maths.h"

class BoxCollider :
	public Component
{
public:
	BoxCollider(Entity &entity);
	void Update(World &world) override;
	void FixedUpdate(World &world) override;
	~BoxCollider();
	Vector3f m_center;
	Vector3f m_minDimensions;
	Vector3f m_maxDimensions;
};

