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
		m_components[i]->Update(world);
	}
}

void Entity::fixedUpdate(World &world)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->FixedUpdate(world);
	}
}

void Entity::createChild(bool active)
{
	Entity newChild(active, *this);
	m_children.push_back(newChild);
}

Entity::~Entity()
{
	for (int i = 0; i < m_components.size(); i++)
	{
		delete(m_components[i]);
	}
	m_components.clear();
}
