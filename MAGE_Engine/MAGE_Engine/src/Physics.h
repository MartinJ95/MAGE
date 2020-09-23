#pragma once
#include "Maths.h"

class Entity;
class RigidBody;
class World;
class SphereCollider;
class PlaneCollider;

enum class collisionTypes
{
	eSphereToSphere,
	eSphereToPlane
};

struct collisionData
{
	collisionData(bool &collided, float &penetrationDepth, Vector3f &collisionNormal) : 
		m_hasCollided(collided), 
		m_penetrationDepth(penetrationDepth), 
		m_collisionNormal(collisionNormal){}
	collisionData(bool collided, float penetrationDepth, Vector3f collisionNormal) :
		m_hasCollided(collided),
		m_penetrationDepth(penetrationDepth),
		m_collisionNormal(collisionNormal) {}
	bool m_hasCollided;
	float m_penetrationDepth;
	Vector3f m_collisionNormal;
};

class Physics
{
public:
	Physics();
	void applyForces(const World &world, RigidBody &body);
	void handleCollisions(RigidBody &body, World &world);
	collisionData detectCollision(Entity &entity1, Entity &entity2);
	collisionData detectCollisions(SphereCollider &collider1, SphereCollider &collider2);
	collisionData detectCollisions(SphereCollider &collider1, PlaneCollider &collider2);
	void collisionResponse(RigidBody &object1, RigidBody &object2, collisionData &collisionData);
	void collisionResponse(RigidBody &object, collisionData &data);
	~Physics();
	float m_gravity;
	float m_velocityDropoff;
};

