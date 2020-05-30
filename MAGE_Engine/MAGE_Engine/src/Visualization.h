#pragma once
#include <unordered_map>
#include <glad/glad.h>
#include <glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MeshGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Visualization
{
public:
	Visualization(const int screenWidth, const int screenHeight, const std::string &windowName);
	bool initialise();
	void generateShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &shaderName);
	bool isOpen() const;
	void clear();
	void display();
	void generateTexture(const std::string &textureFilePath, const std::string &textureName);
	void useShader(const std::string &shaderName);
	void setShaderUniformFloat(const std::string &shaderName, const std::string &uniformName, const float value);
	void setShaderUniformInt(const std::string &shaderName, const std::string &uniformName, const int value);
	void setShaderUniformBool(const std::string &shaderName, const std::string &uniformName, const bool value);
	void setShaderUniformMatrix4f(const std::string &shaderName, const std::string &uniformName, const glm::mat4 &matrix);
	~Visualization();
private:
	GLuint compileShader(const std::string &shaderType, const std::string &shaderFileName);
	GLFWwindow* m_window;
	int m_screenWidth, m_screenHeight;
	std::string m_windowName;
	std::unordered_map <std::string, MeshGL> m_meshes;
	std::unordered_map <std::string, GLuint> m_textures;
	std::unordered_map <std::string, GLuint> m_shaderPrograms;
};

