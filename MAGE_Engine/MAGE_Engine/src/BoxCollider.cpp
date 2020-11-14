#include "BoxCollider.h"



BoxCollider::BoxCollider(Entity &entity) :
	Component(entity), m_center(Vector3f(0, 0, 0)), m_minDimensions(Vector3f(0, 0, 0)), m_maxDimensions(Vector3f(0, 0, 0))
{
}

void BoxCollider::Update(World & world)
{
}

void BoxCollider::FixedUpdate(World & world)
{
}

BoxCollider::~BoxCollider()
{
}
