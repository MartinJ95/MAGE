#pragma once
#include <vector>
#include "Component.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class World;

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
