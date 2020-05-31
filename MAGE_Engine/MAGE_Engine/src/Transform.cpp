#include "Transform.h"
#include "Entity.h"
#include "World.h"

Transform::Transform(Entity& entity) :
	Component(entity),
	m_position(0, 0, 0),
	m_scale(1, 1, 1),
	m_rotation(0, 0, 0)
{

}

void Transform::Update(World & world)
{
}

void Transform::FixedUpdate(World & world)
{
}

Transform::~Transform()
{

}
