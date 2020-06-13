#pragma once

class RigidBody;
class World;

class Physics
{
public:
	Physics();
	void applyForces(const World &world, RigidBody &body);
	~Physics();
	float m_gravity;
	float m_velocityDropoff;
};

