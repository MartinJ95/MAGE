#include "PlaneCollider.h"
#include "RigidBody.h"
#include "PlaneCollider.h"
#include "SphereCollider.h"



PlaneCollider::PlaneCollider(Entity &entity) :
	Component(entity),
	m_normal(Vector3f(1, 0, 0)),
	m_position(Vector3f(0, 0, 0))
{
}

void PlaneCollider::Update(World & world)
{
}

void PlaneCollider::FixedUpdate(World & world)
{
}


PlaneCollider::~PlaneCollider()
{
}
