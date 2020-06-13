#include "Transform.h"
#include "Entity.h"
#include "World.h"

Transform::Transform(Entity& entity) :
	Component(entity),
	m_forward(0, 0, 1),
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

void Transform::updateDirection()
{
	snapRotation(m_rotation);
	applyEulerToForward(m_rotation, m_forward);
}

void Transform::updateRotation(World &world)
{
	m_rotation.x = m_forward.angleBetween(world.m_worldUp) - 90;
	m_rotation.y = m_forward.angleBetween(world.m_worldForward);
	// todo
	// learn how to properly transform a direction to euler angles
	// improve this to find rotation values from a direction
}

void Transform::snapRotation(Vector3f & rotation)
{
	if (rotation.x > 89) rotation.x = 89;
	else if (rotation.x < -89) rotation.x = -89;

	while (rotation.y > 180) rotation.y -= 360;
	while (rotation.y < -180) rotation.y += 360;

	while (rotation.z > 180) rotation.z -= 360;
	while (rotation.z < -180) rotation.z += 360;
}

void Transform::applyEulerToForward(const Vector3f & rotation, Vector3f & forward)
{
	forward.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	forward.y = sin(glm::radians(rotation.x));
	forward.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	forward.normaliseInPlace();
}

Vector3f Transform::worldForward()
{
	Vector3f forward;
	Vector3f rotation = worldRotation();
	snapRotation(rotation);
	applyEulerToForward(rotation, forward);
	return forward;
}

Vector3f Transform::worldPosition()
{
	if (m_entity.m_parent != nullptr)
	{
		return m_position + m_entity.m_parent->getComponent<Transform>()->worldPosition();
	}
	else
	{
		return m_position;
	}
}

Vector3f Transform::worldScale()
{
	if (m_entity.m_parent != nullptr)
	{
		return m_scale + m_entity.m_parent->getComponent<Transform>()->worldScale();
	}
	else
	{
		return m_scale;
	}
}

Vector3f Transform::worldRotation()
{
	if (m_entity.m_parent != nullptr)
	{
		return m_rotation + m_entity.m_parent->getComponent<Transform>()->worldRotation();
	}
	else
	{
		return m_rotation;
	}
}

Transform::~Transform()
{

}
