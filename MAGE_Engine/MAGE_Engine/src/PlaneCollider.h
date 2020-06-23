#pragma once
#include "Component.h"
#include "Maths.h"

class PlaneCollider :
	public Component
{
public:
	PlaneCollider(Entity &entity);
	void Update(World &world) override;
	void FixedUpdate(World &world) override;
	~PlaneCollider();
	Vector3f m_normal;
	Vector3f m_position;
};

