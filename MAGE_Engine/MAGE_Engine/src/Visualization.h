#pragma once
#include <map>
#include <glfw3.h>
#include <string>
#include "MeshGL.h"

class Visualization
{
public:
	Visualization(int screenWidth, int screenHeight, std::string windowName);
	bool initialise();
	bool isOpen() const;
	void clear();
	void display();
	~Visualization();
private:
	GLFWwindow* m_window;
	int m_screenWidth, m_screenHeight;
	std::string m_windowName;
	std::map <std::string, MeshGL> meshes;
};

