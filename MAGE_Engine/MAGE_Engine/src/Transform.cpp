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
	if (m_rotation.x > 89) m_rotation.x = 89;
	else if (m_rotation.x < -89) m_rotation.x = -89;

	while (m_rotation.y > 180) m_rotation.y -= 360;
	while (m_rotation.y < -180) m_rotation.y += 360;

	while (m_rotation.z > 180) m_rotation.z -= 360;
	while (m_rotation.z < -180) m_rotation.z += 360;

	m_forward.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
	m_forward.y = sin(glm::radians(m_rotation.x));
	m_forward.z = sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
	m_forward.normaliseInPlace();
}

Transform::~Transform()
{

}
