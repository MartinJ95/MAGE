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
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Transform;

class Visualization
{
public:
	Visualization(const int screenWidth, const int screenHeight, const std::string &windowName);
	bool initialise();
	void generateShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &shaderName);
	bool isOpen() const;
	void clear();
	void render2D(const std::string &meshName, const std::string &TextureName, const std::string &shaderName, const Transform &transform);
	void display();
	void generateTexture(const std::string &textureFilePath, const std::string &textureName);
	void generateMesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::string &meshName);
	void useShader(const std::string &shaderName);
	void setShaderUniformFloat(const std::string &shaderName, const std::string &uniformName, const float value);
	void setShaderUniformInt(const std::string &shaderName, const std::string &uniformName, const int value);
	void setShaderUniformBool(const std::string &shaderName, const std::string &uniformName, const bool value);
	void setShaderUniformMatrix4f(const std::string &shaderName, const std::string &uniformName, const glm::mat4 &matrix);
	~Visualization();
	int m_screenWidth, m_screenHeight;
private:
	GLuint compileShader(const std::string &shaderType, const std::string &shaderFileName);
	GLFWwindow* m_window;
	std::string m_windowName;
	std::unordered_map <std::string, MeshGL*> m_meshes;
	std::unordered_map <std::string, GLuint> m_textures;
	std::unordered_map <std::string, GLuint> m_shaderPrograms;
};

