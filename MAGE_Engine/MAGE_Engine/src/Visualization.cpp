#include "Visualization.h"

Visualization::Visualization(int screenWidth, int screenHeight, std::string windowName)
	: m_screenWidth(screenWidth),
	m_screenHeight(screenHeight),
	m_windowName(windowName)
{
	
}

bool Visualization::initialise()
{
	/* Initialize the library GLFW */
	if (!glfwInit())
	{
		return false;
	}
	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, m_windowName.c_str(), NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		{
			return false;
		}
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);
	return true;
}

bool Visualization::isOpen() const
{
	if (!glfwWindowShouldClose(m_window))
	{
		return true;
	}
	return false;
}

void Visualization::clear()
{
	if (!glfwWindowShouldClose(m_window))
	{
		glClearColor(0.f, 0.25f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		return;
	}
	return;
}

void Visualization::display()
{
	if (!glfwWindowShouldClose(m_window))
	{
		glfwSwapBuffers(m_window);
		return;
	}
	return;
}

Visualization::~Visualization()
{
	glfwTerminate();
}
