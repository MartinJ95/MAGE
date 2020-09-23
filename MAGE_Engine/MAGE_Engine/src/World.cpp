#include "World.h"

World::World(const int screenWidth, const int screenHeight, const std::string &windowName) :
	m_viz(screenWidth, screenHeight, windowName),
	m_physics(),
	m_entities(),
	m_worldUp(0, 1, 0),
	m_worldForward(1, 0, 0),
	m_worldRight(0, 0, 1),
	m_mainCamera(nullptr)
{

}

bool World::Initualize()
{
	if (!m_viz.initialise())
	{
		return false;
	}
	m_viz.generateShader("src\\default2DShader.vs", "src\\default2DShader.fs", "default2DShader");
	m_viz.generateShader("src\\default3DShader.vs", "src\\default3DShader.fs", "default3DShader");
	m_viz.generateTexture("Resources\\mageIntro.png", "introTexture");
	m_viz.generateTexture("Resources\\wall.png", "wall");
	m_viz.generateTexture("Resources\\floor.png", "floor");

	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices2;
	std::vector<unsigned int> indices{0, 1, 2, 2, 1, 3};

	Vertex v1;
	v1.position = Vector3f(-1, -1, 0);
	v1.color = Vector3f(0, 0, 0);
	v1.normal = Vector3f(0, 0, 0);
	v1.texCoords = Vector2f(0, 0);

	Vertex v2;
	v2.position = Vector3f(1, -1, 0);
	v2.color = Vector3f(0, 0, 0);
	v2.normal = Vector3f(0, 0, 0);
	v2.texCoords = Vector2f(1, 0);

	Vertex v3;
	v3.position = Vector3f(-1, 1, 0);
	v3.color = Vector3f(0, 0, 0);
	v3.normal = Vector3f(0, 0, 0);
	v3.texCoords = Vector2f(0, 1);

	Vertex v4;
	v4.position = Vector3f(1, 1, 0);
	v4.color = Vector3f(0, 0, 0);
	v4.normal = Vector3f(0, 0, 0);
	v4.texCoords = Vector2f(1, 1);

	Vertex v21;
	v21.position = Vector3f(-25, -25, 0);
	v21.color = Vector3f(0, 0, 0);
	v21.normal = Vector3f(0, 0, 0);
	v21.texCoords = Vector2f(0, 0);

	Vertex v22;
	v22.position = Vector3f(25, -25, 0);
	v22.color = Vector3f(0, 0, 0);
	v22.normal = Vector3f(0, 0, 0);
	v22.texCoords = Vector2f(5, 0);

	Vertex v23;
	v23.position = Vector3f(-25, 25, 0);
	v23.color = Vector3f(0, 0, 0);
	v23.normal = Vector3f(0, 0, 0);
	v23.texCoords = Vector2f(0, 5);

	Vertex v24;
	v24.position = Vector3f(25, 25, 0);
	v24.color = Vector3f(0, 0, 0);
	v24.normal = Vector3f(0, 0, 0);
	v24.texCoords = Vector2f(5, 5);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	vertices2.push_back(v21);
	vertices2.push_back(v22);
	vertices2.push_back(v23);
	vertices2.push_back(v24);

	m_viz.generateMesh(vertices, indices, "default2DMesh");
	m_viz.generateMesh(vertices2, indices, "wall");

	Entity *cam = new Entity(true);
	cam->addComponent<Transform>();
	cam->getComponent<Transform>()->m_position = Vector3f(0, 45, 0);
	cam->getComponent<Transform>()->m_rotation = Vector3f(-45, -90, 0);
	cam->getComponent<Transform>()->updateDirection();
	cam->addComponent<Camera>();
	cam->addComponent<RigidBody>();
	cam->getComponent<RigidBody>()->m_force = Vector3f(0.002, 0, 0.003);
	cam->addComponent<SphereCollider>();
	cam->getComponent<SphereCollider>()->m_radius = 5.f;
	m_mainCamera = cam->getComponent<Camera>();

	m_entities.emplace_back(cam);

	Entity *floor = new Entity(true);
	floor->addComponent<Transform>();
	floor->getComponent<Transform>()->m_position = Vector3f(0, 0, 0);
	floor->getComponent<Transform>()->m_rotation.x = 90;
	floor->getComponent<Transform>()->m_scale = Vector3f(1, 1, 1);
	floor->addComponent<Mesh>();
	floor->getComponent<Mesh>()->m_meshName = "wall";
	floor->getComponent<Mesh>()->m_shaderName = "default3DShader";
	floor->getComponent<Mesh>()->m_textureName = "floor";
	floor->addComponent<PlaneCollider>();
	floor->getComponent<PlaneCollider>()->m_normal = Vector3f(0, 1, 0);
	
	m_entities.emplace_back(floor);
	
	Entity *wall1 = new Entity(true);
	wall1->addComponent<Transform>();
	wall1->getComponent<Transform>()->m_position = Vector3f(25, 25, 0);
	wall1->getComponent<Transform>()->m_scale = Vector3f(1, 1, 1);
	wall1->getComponent<Transform>()->m_rotation.y = 90;
	wall1->addComponent<Mesh>();
	wall1->getComponent<Mesh>()->m_meshName = "wall";
	wall1->getComponent<Mesh>()->m_shaderName = "default3DShader";
	wall1->getComponent<Mesh>()->m_textureName = "wall";
	wall1->addComponent<PlaneCollider>();
	wall1->getComponent<PlaneCollider>()->m_normal = Vector3f(-1, 0, 0);

	m_entities.emplace_back(wall1);
	
	
	Entity *wall2 = new Entity(true);
	wall2->addComponent<Transform>();
	wall2->getComponent<Transform>()->m_position = Vector3f(-25, 25, 0);
	wall2->getComponent<Transform>()->m_scale = Vector3f(1, 1, 1);
	wall2->getComponent<Transform>()->m_rotation.y = 90;
	wall2->addComponent<Mesh>();
	wall2->getComponent<Mesh>()->m_meshName = "wall";
	wall2->getComponent<Mesh>()->m_shaderName = "default3DShader";
	wall2->getComponent<Mesh>()->m_textureName = "wall";
	wall2->addComponent<PlaneCollider>();
	wall2->getComponent<PlaneCollider>()->m_normal = Vector3f(1, 0, 0);

	m_entities.emplace_back(wall2);

	Entity *wall3 = new Entity(true);
	wall3->addComponent<Transform>();
	wall3->getComponent<Transform>()->m_position = Vector3f(0, 25, 25);
	wall3->getComponent<Transform>()->m_scale = Vector3f(1, 1, 1);
	wall3->addComponent<Mesh>();
	wall3->getComponent<Mesh>()->m_meshName = "wall";
	wall3->getComponent<Mesh>()->m_shaderName = "default3DShader";
	wall3->getComponent<Mesh>()->m_textureName = "wall";
	wall3->addComponent<PlaneCollider>();
	wall3->getComponent<PlaneCollider>()->m_normal = Vector3f(0, 0, -1);

	m_entities.emplace_back(wall3);

	Entity *wall4 = new Entity(true);
	wall4->addComponent<Transform>();
	wall4->getComponent<Transform>()->m_position = Vector3f(0, 25, -25);
	wall4->getComponent<Transform>()->m_scale = Vector3f(1, 1, 1);
	wall4->addComponent<Mesh>();
	wall4->getComponent<Mesh>()->m_meshName = "wall";
	wall4->getComponent<Mesh>()->m_shaderName = "default3DShader";
	wall4->getComponent<Mesh>()->m_textureName = "wall";
	wall4->addComponent<PlaneCollider>();
	wall4->getComponent<PlaneCollider>()->m_normal = Vector3f(0, 0, 1);

	m_entities.emplace_back(wall4);
	
	
	Entity *e = new Entity(true);
	e->addComponent<Transform>();
	e->addComponent<Mesh>();
	Transform * t = e->getComponent<Transform>();
	t->m_position = Vector3f(m_viz.m_screenWidth / 2, m_viz.m_screenHeight / 2, 0);
	t->m_scale = Vector3f(m_viz.m_screenWidth / 4, m_viz.m_screenHeight / 4, 1);
	t->m_rotation = Vector3f(0, 0, 0);

	Mesh * m = e->getComponent<Mesh>();
	m->m_is3D = false;
	m->m_meshName = "default2DMesh";
	m->m_shaderName = "default2DShader";
	m->m_textureName = "introTexture";

	m_entities.emplace_back(e);

	return true;
}

void World::Run()
{
	while (m_viz.isOpen())
	{
		m_viz.clear();

		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Update(*this);
		}

		m_mainCamera->m_entity.getComponent<Transform>()->m_rotation.y -= 0.1;
		m_mainCamera->m_entity.getComponent<Transform>()->updateDirection();

		m_viz.display();

		glfwPollEvents();
	}
}

World::~World()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		delete m_entities[i];
	}
}
