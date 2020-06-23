#pragma once
#include "Component.h"
#include "Maths.h"

class SphereCollider :
	public Component
{
public:
	SphereCollider(Entity &entity);
	void Update(World &world) override;
	void FixedUpdate(World &world) override;
	~SphereCollider();
	float m_radius;
	Vector3f m_center;
};

