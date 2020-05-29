#include "MeshGL.h"

MeshGL::MeshGL() : 
	m_vertices(),
	m_indices(),
	m_elementCount(),
	m_VertexVBO(0),
	m_IndexIBO(0),
	m_MeshVAO(0)
{
}

MeshGL::MeshGL(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices) : 
	m_vertices(vertices),
	m_indices(indices),
	m_elementCount(),
	m_VertexVBO(0),
	m_IndexIBO(0),
	m_MeshVAO(0)
{
}

void MeshGL::initualize()
{
	glGenVertexArrays(1, &m_MeshVAO);
	glBindVertexArray(m_MeshVAO);
	
	glGenBuffers(1, &m_VertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &m_vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(vertexPosition);
	glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(vertexColor);
	glVertexAttribPointer(vertexColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glEnableVertexAttribArray(vertexNormal);
	glVertexAttribPointer(vertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(vertexTexCoords);
	glVertexAttribPointer(vertexTexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IndexIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int), &m_indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void MeshGL::render(const GLuint shader)
{
	glBindVertexArray(m_MeshVAO);
	glDrawElements(GL_TRIANGLES, m_elementCount, GL_UNSIGNED_INT, 0);
}


MeshGL::~MeshGL()
{
	glDeleteBuffers(1, &m_VertexVBO);
	glDeleteBuffers(1, &m_IndexIBO);
	glDeleteVertexArrays(1, &m_MeshVAO);
}
