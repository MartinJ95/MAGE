#include "World.h"

World::World(const int screenWidth, const int screenHeight, const std::string &windowName) :
	m_viz(Visualization(screenWidth, screenHeight, windowName))
{

}

bool World::Initualize()
{
	if (!m_viz.initialise())
	{
		return false;
	}
	return true;
}

void World::Run()
{
	while (m_viz.isOpen())
	{
		m_viz.clear();

		m_viz.display();

		glfwPollEvents();
	}
}

World::~World()
{
}
