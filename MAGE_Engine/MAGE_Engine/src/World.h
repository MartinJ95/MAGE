#pragma once
#include "Visualization.h"
#include "InputManager.h"
#include "Physics.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "Camera.h"
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
	InputManager *m_input;
	Physics m_physics;
	std::vector<Entity*> m_entities;
	Vector3f m_worldUp;
	Vector3f m_worldForward;
	Vector3f m_worldRight;
	Camera *m_mainCamera;
};

