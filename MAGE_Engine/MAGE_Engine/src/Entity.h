#pragma once
#include <vector>
#include "Component.h"
#include "Camera.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class World;

typedef bool(*componentFunction)(Component&, World&);

typedef bool(*componentManager)(Component*, World*, int);

template<typename T> bool manageComponents(Component *component, World *world, int functionNumber)
{
	switch(functionNumber)
	{
	case 0:
		return Entity::updateComponent<T>(component, *world);
	case 1:
		return Entity::FixedUpdateComponent<T>(component, *world);
	case 2:
		return Entity::CleanUpComponent<T>(component);
	default:
		return false;
	}
}

static componentManager const componentManagerTypes[] =
{ manageComponents<Transform>,
manageComponents<Camera>,
manageComponents<Mesh>,
manageComponents<RigidBody>
};

class Entity
{
public:
	Entity(bool active);
	Entity(bool active, Entity &parent);
	template<typename T> T* getComponent()
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			if (dynamic_cast<T*>(m_components[i]) != NULL)
			{
				return static_cast<T*>(m_components[i]);
			}
		}
		return NULL;
	}
	template<typename T> void addComponent()
	{
		if (std::is_base_of<Component, T>::value == true)
		{
			T *newComponent = new T(*this);
			m_components.emplace_back(newComponent);
		}
	}
	template<typename T> static bool updateComponent(Component *component, World &world)
	{
		if (dynamic_cast<T*>(component) != NULL)
		{
			T *c = static_cast<T*>(component);
			c->Update(world);
			return true;
		}
		return false;
	}
	template<typename T> static bool FixedUpdateComponent(Component *component, World &world)
	{
		if (dynamic_cast<T*>(component) != NULL)
		{
			T *c = static_cast<T*>(component);
			c->FixedUpdate(world);
			return true;
		}
		return false;
	}
	template<typename T> static bool CleanUpComponent(Component *component)
	{
		if (dynamic_cast<T*>(component) != NULL)
		{
			T *c = static_cast<T*>(component);
			delete(c);
			return true;
		}
		return false;
	}
	void Update(World &world);
	void fixedUpdate(World &world);
	void createChild(bool active);
	glm::mat4 getTransformMatrix2D(World &world);
	glm::mat4 getTransformMatrix3D(World &world);
	~Entity();
	bool m_active;
	Entity *m_parent;
	std::vector<Entity> m_children;
private:
	std::vector<Component*> m_components;
};




