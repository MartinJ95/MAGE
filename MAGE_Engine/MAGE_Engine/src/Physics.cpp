#include "Physics.h"
#include "Entity.h"
#include "World.h"
#include "RigidBody.h"
#include "Entity.h"


Physics::Physics() :
	m_gravity(0.009),
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

void Physics::handleCollisions(RigidBody & body, World & world)
{
	colliderTypes collider1 = body.m_entity.getCollider();
	if (collider1 != colliderTypes::eNone)
	{
		for (int i = 0; i < world.m_entities.size(); i++)
		{
			RigidBody *r = world.m_entities[i]->getComponent<RigidBody>();
			if (world.m_entities[i]->getCollider() != colliderTypes::eNone && r != &body)
			{
				colliderTypes collider2 = world.m_entities[i]->getCollider();
				if (collider2 != colliderTypes::eNone)
				{
					if (collider1 == colliderTypes::eSphere && collider2 == colliderTypes::eSphere)
					{
						
					}
					else if (collider1 == colliderTypes::eSphere && collider2 == colliderTypes::ePlane)
					{
						collisionData data = detectCollisions(*body.m_entity.getComponent<SphereCollider>(), *world.m_entities[i]->getComponent<PlaneCollider>());
						if (data.m_hasCollided == true)
						{
							collisionResponse(body, data);
						}
					}
					else if (collider1 == colliderTypes::ePlane && collider2 == colliderTypes::eSphere)
					{

					}
				}
			}
		}
	}
}

collisionData Physics::detectCollision(Entity & entity1, Entity & entity2)
{
	colliderTypes collider1 = entity1.getCollider();
	colliderTypes collider2 = entity2.getCollider();
	if (collider1 != colliderTypes::eNone && collider2 != colliderTypes::eNone)
	{
		if (collider1 & collider2 == colliderTypes::eSphere)
		{
			return detectCollisions(*entity1.getComponent<SphereCollider>(), *entity2.getComponent<SphereCollider>());
		}
		else if (collider1 == colliderTypes::eSphere && collider2 == colliderTypes::ePlane)
		{
			return detectCollisions(*entity1.getComponent<SphereCollider>(), *entity2.getComponent<PlaneCollider>());
		}
		else if (collider1 == colliderTypes::ePlane && collider2 == colliderTypes::eSphere)
		{
			return detectCollisions(*entity2.getComponent<SphereCollider>(), *entity1.getComponent<PlaneCollider>());
		}
	}
}

collisionData Physics::detectCollisions(SphereCollider &collider1, SphereCollider &collider2)
{
	Vector3f vectorBetween = ((collider1.m_entity.getComponent<Transform>()->m_position + collider1.m_center) + (collider2.m_entity.getComponent<Transform>()->m_position + collider2.m_center));
	Vector3f collisionNormal = Vector3f(0, 0, 0);
	if (vectorBetween.length() < collider1.m_radius + collider2.m_radius)
	{
		return collisionData(true, (collider1.m_radius + collider2.m_radius) - vectorBetween.length(), collisionNormal);
	}
	else
	{
		return collisionData(false, 0, collisionNormal);
	}
}

collisionData Physics::detectCollisions(SphereCollider &collider1, PlaneCollider &collider2)
{
	Vector3f vectorBetween = ((collider1.m_entity.getComponent<Transform>()->m_position + collider1.m_center) - (collider2.m_entity.getComponent<Transform>()->m_position + collider2.m_position));
	Vector3f collisionNormal = collider2.m_normal;
	if (vectorBetween.dotProduct(collisionNormal) < collider1.m_radius)
	{
		float penetrationDepth = collider1.m_radius - vectorBetween.dotProduct(collisionNormal);
		if (penetrationDepth < 0)
		{
			penetrationDepth = -penetrationDepth;
		}
		return collisionData(true, penetrationDepth, collisionNormal);
	}
	else
	{
		return collisionData(false, 0, Vector3f(0, 0, 0));
	}
}

void Physics::collisionResponse(RigidBody & object1, RigidBody & object2, collisionData & collisionData)
{
}

void Physics::collisionResponse(RigidBody & object, collisionData & data)
{
	Transform *t = object.m_entity.getComponent<Transform>();
	t->m_position = t->m_position + (data.m_collisionNormal * data.m_penetrationDepth);
	object.m_velocity = object.m_velocity.reflect(data.m_collisionNormal);
	//temp
	object.m_force = object.m_force.reflect(data.m_collisionNormal);
}


Physics::~Physics()
{
}
