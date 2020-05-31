#pragma once
#include <vector>
#include "Component.h"
#include "Transform.h"

class World;

class Entity
{
public:
	Entity(bool active);
	Entity(bool active, Entity &parent);
	template<typename T> Component* getComponent()
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			if (dynamic_cast<T*>(m_components[i]) != NULL)
			{
				return m_components[i];
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
	void Update(World &world);
	void fixedUpdate(World &world);
	void createChild(bool active);
	~Entity();
	bool m_active;
	Entity *m_parent;
	std::vector<Entity> m_children;
private:
	std::vector<Component*> m_components;
};
