#pragma once
#include "Maths.h"

class Entity;
class RigidBody;
class World;
class SphereCollider;
class PlaneCollider;
class BoxCollider;

enum class collisionTypes
{
	eSphereToSphere,
	eSphereToPlane,
	eSphereToBox
};

struct collisionData
{
	collisionData(const bool &collided, const float &penetrationDepth, const Vector3f &collisionNormal, Entity *entity = nullptr) : 
		m_hasCollided(collided), 
		m_penetrationDepth(penetrationDepth), 
		m_collisionNormal(collisionNormal),
	collidedEntity(entity){}
	bool m_hasCollided;
	float m_penetrationDepth;
	Vector3f m_collisionNormal;
	Entity *collidedEntity;
};

class Physics
{
public:
	Physics();
	void applyForces(const World &world, RigidBody &body);
	void handleCollisions(Entity &entity, World &world);
	collisionData detectCollision(Entity &entity1, World &world);
	collisionData detectCollisions(SphereCollider &collider1, SphereCollider &collider2);
	collisionData detectCollisions(SphereCollider &collider1, PlaneCollider &collider2);
	collisionData detectCollisions(SphereCollider &collider1, BoxCollider &collider2);
	void collisionResponse(RigidBody &object1, RigidBody &object2, collisionData &collisionData);
	void collisionResponse(RigidBody &object, collisionData &data);
	~Physics();
	float m_gravity;
	float m_velocityDropoff;
	Vector3f compass[6]
	{
		Vector3f(1, 0, 0),
		Vector3f(0, 1, 0),
		Vector3f(0, 0, 1),
		Vector3f(-1, 0, 0),
		Vector3f(0, -1, 0),
		Vector3f(0, 0, -1)
	};
};

