#pragma once
#include "Visualization.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "MeshGL.h"
#include <vector>

class World
{
public:
	World(const int screenWidth, const int screenHeight, const std::string &windowName);
	bool Initualize();
	void Run();
	~World();
	Visualization m_viz;
	std::vector<Entity*> m_entities;
};

