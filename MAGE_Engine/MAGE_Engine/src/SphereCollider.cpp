#include "SphereCollider.h"



SphereCollider::SphereCollider(Entity &entity) :
	Component(entity),
	m_radius(0.5),
	m_center(Vector3f(0, 0, 0))
{
}

void SphereCollider::Update(World & world)
{
}

void SphereCollider::FixedUpdate(World & world)
{
}


SphereCollider::~SphereCollider()
{
}
