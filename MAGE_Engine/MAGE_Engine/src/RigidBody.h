#pragma once
#include "Component.h"
#include "maths.h"

class RigidBody :
	public Component
{
public:
	RigidBody(Entity &entity);
	void Update(World &world) override;
	void FixedUpdate(World &world) override;
	~RigidBody();
	float m_mass;
	Vector3f m_velocity;
	Vector3f m_force;
	Vector3f m_impulseForce;
};

