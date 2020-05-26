#pragma once
#include <map>
#include <glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MeshGL.h"

class Visualization
{
public:
	Visualization(int screenWidth, int screenHeight, std::string windowName);
	bool initialise();
	void generateShader(std::string vertexShader, std::string fragmentShader, std::string shaderName);
	bool isOpen() const;
	void clear();
	void display();
	~Visualization();
private:
	GLuint compileShader(std::string shaderType, std::string shaderFileName);
	GLFWwindow* m_window;
	int m_screenWidth, m_screenHeight;
	std::string m_windowName;
	std::map <std::string, MeshGL> meshes;
	std::map <std::string, GLuint> shaderPrograms;
};

