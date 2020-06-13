#include "Physics.h"
#include "World.h"
#include "RigidBody.h"
#include "Entity.h"


Physics::Physics() :
	m_gravity(9),
	m_velocityDropoff(0.98)
{
}

void Physics::applyForces(const World & world, RigidBody & body)
{
	body.m_velocity += (body.m_force + body.m_impulseForce + world.m_worldUp * -m_gravity) / body.m_mass;
	body.m_impulseForce = Vector3f(0, 0, 0);
	body.m_velocity *= m_velocityDropoff;
	body.m_entity.getComponent<Transform>()->m_position += body.m_velocity;
}


Physics::~Physics()
{
}
