#include "Entity.h"
#include "World.h"


Entity::Entity(bool active) :
	m_active(active),
	m_parent(nullptr),
	m_children(),
	m_components()
{
}

Entity::Entity(bool active, Entity &parent) :
	m_active(active),
	m_parent(&parent),
	m_children(),
	m_components()
{
}

void Entity::Update(World &world)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		for (auto f : componentManagerTypes)
		{
			if (f(m_components[i], &world, 0) == true)
			{
				break;
			}
		}
	}
}

void Entity::fixedUpdate(World &world)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		for (auto f : componentManagerTypes)
		{
			if (f(m_components[i], &world, 1) == true)
			{
				break;
			}
		}
	}
}

void Entity::createChild(bool active)
{
	Entity newChild(active, *this);
	m_children.push_back(newChild);
}

glm::mat4 Entity::getTransformMatrix2D(World &world)
{
	Transform *t = getComponent<Transform>();
	glm::mat4 transformMatrix = glm::mat4(1.f);
	float meshSizeX = 1;
	float meshSizeY = 1;
	meshSizeX /= world.m_viz.m_screenWidth;
	meshSizeY /= world.m_viz.m_screenHeight;
	transformMatrix = glm::translate(transformMatrix, glm::vec3((((t->m_position.x / world.m_viz.m_screenWidth) * 2) - 1), (((t->m_position.y / world.m_viz.m_screenHeight) * 2) - 1), t->m_position.z));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(t->m_rotation.x), glm::vec3(1, 0, 0));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(t->m_rotation.y), glm::vec3(0, 1, 0));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(t->m_rotation.z), glm::vec3(0, 0, 1));
	transformMatrix = glm::scale(transformMatrix, glm::vec3(meshSizeX *t->m_scale.x, meshSizeY *t->m_scale.y, t->m_scale.y));
	return transformMatrix;
}

glm::mat4 Entity::getTransformMatrix3D(World &world)
{
	Transform *t = getComponent<Transform>();
	glm::mat4 transformMatrix = glm::mat4(1.f);
	transformMatrix = glm::translate(transformMatrix, glm::vec3(t->m_position.x, t->m_position.y, t->m_position.z));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(t->m_rotation.x), glm::vec3(1, 0, 0));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(t->m_rotation.y), glm::vec3(0, 1, 0));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(t->m_rotation.z), glm::vec3(0, 0, 1));
	transformMatrix = glm::scale(transformMatrix, glm::vec3(t->m_scale.x, t->m_scale.y, t->m_scale.z));
	return transformMatrix;
}

Entity::~Entity()
{
	for (int i = 0; i < m_components.size(); i++)
	{
		for (auto f : componentManagerTypes)
		{
			if (f(m_components[i], nullptr, 2) == true)
			{
				break;
			}
		}
	}
	m_components.clear();
}
