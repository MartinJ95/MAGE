//#include <GLFW/glfw3.h>
//
//int main(void)
//{
//	GLFWwindow* window;
//
//	/* Initialize the library */
//	if (!glfwInit())
//	{
//		return -1;
//	}
//
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		{
//			return -1;
//		}
//	}
//
//
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* Render here */
//		glClearColor(0.f, 0.25f, 0.5f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}

#include "Visualization.h"
#include "Maths.h"
#include <iostream>



int main(void)
{
	Visualization viz(640, 480, "MAGE");

	if (!viz.initialise())
	{
		return -1;
	}
	while (viz.isOpen())
	{
		viz.clear();


		viz.display();


		glfwPollEvents();
	}

	return 0;
}