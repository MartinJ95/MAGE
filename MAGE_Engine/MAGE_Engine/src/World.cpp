#include "World.h"

World::World(const int screenWidth, const int screenHeight, const std::string &windowName) :
	m_viz(screenWidth, screenHeight, windowName),
	m_input(new InputManager(nullptr)),
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
	m_input->m_window = m_viz.getWindow();
	ActiveInputManager = m_input;
	m_viz.generateShader("src\\default2DShader.vs", "src\\default2DShader.fs", "default2DShader");
	m_viz.generateShader("src\\default3DShader.vs", "src\\default3DShader.fs", "default3DShader");
	m_viz.generateTexture("Resources\\mageIntro.png", "introTexture");
	m_viz.generateTexture("Resources\\wall.png", "wall");
	m_viz.generateTexture("Resources\\floor.png", "floor");
	m_viz.generateTexture("Resources\\box.png", "box");
	m_viz.generateTexture("Resources\\world.png", "world");

	m_viz.generateSquareMesh(-1, 1, 0, 1, "default2DMesh");
	m_viz.generateSquareMesh(-25, 25, 0, 5, "wall");
	m_viz.generateBoxMesh(-1, 1, 0, 1, "box");
	m_viz.generateSphereMesh(Vector3f(0, 0, 0), 1, 50, "sphere");

	Entity *cam = new Entity(true);
	cam->addComponent<Transform>();
	cam->getComponent<Transform>()->m_position = Vector3f(0, 45, 0);
	cam->getComponent<Transform>()->m_rotation = Vector3f(-45, -90, 0);
	cam->getComponent<Transform>()->updateDirection();
	cam->addComponent<Camera>();
	cam->addComponent<RigidBody>();
	//cam->getComponent<RigidBody>()->m_force = Vector3f(0.002, 0, 0.003);
	cam->addComponent<SphereCollider>();
	cam->getComponent<SphereCollider>()->m_radius = 2.5f;
	m_mainCamera = cam->getComponent<Camera>();

	m_entities.emplace_back(cam);

	Entity *box = new Entity(true);
	box->addComponent<Transform>();
	box->getComponent<Transform>()->m_position = Vector3f(0, 2, 0);
	box->addComponent<Mesh>();
	box->getComponent<Mesh>()->m_meshName = "box";
	box->getComponent<Mesh>()->m_shaderName = "default3DShader";
	box->getComponent<Mesh>()->m_textureName = "box";
	box->addComponent<BoxCollider>();
	box->getComponent<BoxCollider>()->m_minDimensions = Vector3f(-1, -1, -1);
	box->getComponent<BoxCollider>()->m_maxDimensions = Vector3f(1, 1, 1);

	m_entities.emplace_back(box);

	Entity *sphere = new Entity(true);
	sphere->addComponent<Transform>();
	sphere->getComponent<Transform>()->m_position = Vector3f(0, 2, 5);
	sphere->addComponent<Mesh>();
	sphere->getComponent<Mesh>()->m_meshName = "sphere";
	sphere->getComponent<Mesh>()->m_shaderName = "default3DShader";
	sphere->getComponent<Mesh>()->m_textureName = "world";
	sphere->addComponent<SphereCollider>();
	sphere->getComponent<SphereCollider>()->m_radius = 0.5f;

	m_entities.emplace_back(sphere);


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

		m_input->processInput();

		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Update(*this);
		}

		//m_mainCamera->m_entity.getComponent<Transform>()->m_rotation.y -= 0.1;
		//m_mainCamera->m_entity.getComponent<Transform>()->updateDirection();
		RigidBody *r = m_mainCamera->m_entity.getComponent<RigidBody>();
		if (m_input->getInput("fire1")->m_inputValue == 1)
		{
			glfwSetInputMode(m_viz.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(m_input->m_window, m_input->mouse_callback);
		}
		else
		{
			glfwSetInputMode(m_viz.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPosCallback(m_input->m_window, NULL);
		}
		r->m_entity.getComponent<Transform>()->m_rotation += Vector3f(m_input->getAxis("vertical1")->m_inputValue, m_input->getAxis("horizontal1")->m_inputValue, 0);
		r->m_entity.getComponent<Transform>()->updateDirection();
		ActiveInputManager->getAxis(ActiveInputManager->m_mouseAxis)->m_inputValue = 0;
		ActiveInputManager->getAxis(ActiveInputManager->m_mouseAxis1)->m_inputValue = 0;
		if (m_input->getInput("jump")->m_inputValue == 1)
		{
			r->m_impulseForce += Vector3f(0, 0.05, 0);
		}

		Vector3f movement = (Vector3f(m_input->getAxis("vertical")->m_inputValue, 0, m_input->getAxis("horizontal")->m_inputValue));
		Vector3f forward = r->m_entity.getComponent<Transform>()->m_forward;
		forward.y = 0;
		forward.normaliseInPlace();
		r->m_impulseForce += forward * movement.x * 0.01;
		r->m_impulseForce += forward.crossProduct(m_worldUp) * movement.z * 0.01;
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
