#pragma once
#include <iostream>
#include <vector>
#include <glad.h>
#include <glfw3.h>
#include "Maths.h"

struct Vertex
{
	Maths::Vector3f position;
	Maths::Vector3f normal;
	Maths::Vector2f texCoords;
};

enum VertexAttributes
{
	vertexPosition = 0,
	vertexNormal = 1,
	vertexTexCoords = 2
};

enum FragmentData
{
	FragmentColor = 0
};

class MeshGL
{
public:
	MeshGL();
	MeshGL(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices);
	void initualize();
	void render(const GLuint shader);
	~MeshGL();
	std::string texture;
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	unsigned int m_elementCount;
	GLuint m_VertexVBO{ 0 };
	GLuint m_IndexIBO{ 0 };
	GLuint m_MeshVAO{ 0 };
};