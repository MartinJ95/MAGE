#include "RigidBody.h"
#include "World.h"


RigidBody::RigidBody(Entity &entity) : Component(entity),
	m_mass(1),
	m_restitution(0.9),
	m_velocity(0, 0, 0),
	m_force(0, 0, 0),
	m_impulseForce(0, 0, 0)
{

}

void RigidBody::Update(World &world)
{
	world.m_physics.applyForces(world, *this);
	world.m_physics.handleCollisions(m_entity, world);
}

void RigidBody::FixedUpdate(World &world)
{

}


RigidBody::~RigidBody()
{
}
