#pragma once
#include <unordered_map>
#include <glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MeshGL.h"

class Visualization
{
public:
	Visualization(const int screenWidth, const int screenHeight, const std::string windowName);
	bool initialise();
	void generateShader(const std::string vertexShader, const std::string fragmentShader, const std::string shaderName);
	bool isOpen() const;
	void clear();
	void display();
	~Visualization();
private:
	GLuint compileShader(const std::string &shaderType, const std::string &shaderFileName);
	GLFWwindow* m_window;
	int m_screenWidth, m_screenHeight;
	std::string m_windowName;
	std::unordered_map <std::string, MeshGL> m_meshes;
	std::unordered_map <std::string, GLuint> m_shaderPrograms;
};

