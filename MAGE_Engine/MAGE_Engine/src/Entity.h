#pragma once
#include <vector>
#include "Component.h"


class Entity
{
public:
	Entity();
	template<typename T> Component* getComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (dynamic_cast<T>components[i] != NULL)
			{
				return components[i];
			}
		}
		return NULL;
	}
	~Entity();
private:
	std::vector<Component> components();
};
