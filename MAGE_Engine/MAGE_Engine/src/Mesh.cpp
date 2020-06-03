#include "Mesh.h"
#include "World.h"
#include "Entity.h"
#include "Transform.h"


Mesh::Mesh(Entity &entity) :
	Component(entity),
	m_meshName(),
	m_textureName(),
	m_shaderName()
{
}

void Mesh::Update(World &world)
{
	world.m_viz.render2D(m_meshName, m_textureName, m_shaderName, m_entity.getTransformMatrix2D(world));
}

void Mesh::FixedUpdate(World &world)
{

}


Mesh::~Mesh()
{
}
