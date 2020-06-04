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
		//m_components[i]->Update(world);
		if (dynamic_cast<Transform*>(m_components[i]) != NULL)
		{
			Transform *t = dynamic_cast<Transform*>(m_components[i]);
			t->Update(world);
		}
		else if (dynamic_cast<Mesh*>(m_components[i]) != NULL)
		{
			Mesh *m = dynamic_cast<Mesh*>(m_components[i]);
			m->Update(world);
		}
	}
}

void Entity::fixedUpdate(World &world)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		//m_components[i]->FixedUpdate(world);
		if (dynamic_cast<Transform*>(m_components[i]) != NULL)
		{
			Transform *t = dynamic_cast<Transform*>(m_components[i]);
			t->FixedUpdate(world);
		}
		if (dynamic_cast<Mesh*>(m_components[i]) != NULL)
		{
			Mesh *m = dynamic_cast<Mesh*>(m_components[i]);
			m->FixedUpdate(world);
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
	transformMatrix = glm::scale(transformMatrix, glm::vec3(meshSizeX *t->m_scale.x, meshSizeY *t->m_scale.y, t->m_scale.y));
	transformMatrix = glm::rotate(transformMatrix, t->m_rotation.x, glm::vec3(0, 1, 0));
	transformMatrix = glm::rotate(transformMatrix, t->m_rotation.y, glm::vec3(1, 0, 0));
	transformMatrix = glm::rotate(transformMatrix, t->m_rotation.z, glm::vec3(0, 0, 1));
	transformMatrix = glm::translate(transformMatrix, glm::vec3((((t->m_position.x / world.m_viz.m_screenWidth) * 2) - 1), (((t->m_position.y / world.m_viz.m_screenHeight) * 2) - 1), t->m_position.z));
	return transformMatrix;
}

glm::mat4 Entity::getTransformMatrix3D(World &world)
{
	Transform *t = getComponent<Transform>();
	glm::mat4 transformMatrix = glm::mat4(1.f);
	transformMatrix = glm::scale(transformMatrix, glm::vec3(t->m_scale.x, t->m_scale.y, t->m_scale.z));
	transformMatrix = glm::rotate(transformMatrix, t->m_rotation.x, glm::vec3(0, 1, 0));
	transformMatrix = glm::rotate(transformMatrix, t->m_rotation.y, glm::vec3(1, 0, 0));
	transformMatrix = glm::rotate(transformMatrix, t->m_rotation.z, glm::vec3(0, 0, 1));
	transformMatrix = glm::translate(transformMatrix, glm::vec3(t->m_position.x, t->m_position.y, t->m_position.z));
	return transformMatrix;
}

Entity::~Entity()
{
	for (int i = 0; i < m_components.size(); i++)
	{
		//delete(m_components[i]);
		if (dynamic_cast<Transform*>(m_components[i]) != NULL)
		{
			Transform *t = dynamic_cast<Transform*>(m_components[i]);
			delete t;
		}
		else if (dynamic_cast<Mesh*>(m_components[i]) != NULL)
		{
			Mesh *m = dynamic_cast<Mesh*>(m_components[i]);
			delete m;
		}
	}
	m_components.clear();
}
