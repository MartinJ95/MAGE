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
		if (dynamic_cast<Mesh*>(m_components[i]) != NULL)
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
