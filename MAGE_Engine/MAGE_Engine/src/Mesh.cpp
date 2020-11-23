#include "Mesh.h"
#include "World.h"
#include "Entity.h"
#include "Transform.h"


Mesh::Mesh(Entity &entity) :
	Component(entity),
	m_is3D(true),
	m_meshName(),
	m_textureName(),
	m_shaderName()
{
}

void Mesh::Update(World &world)
{
	if (!m_is3D)
	{
		world.m_viz.render2D(m_meshName, m_textureName, m_shaderName, m_entity.getTransformMatrix2D(world));
	}
	else
	{
		world.m_viz.render3D(m_meshName, m_textureName, m_shaderName, m_entity.getTransformMatrix3D(world), *world.m_mainCamera, world.m_worldUp, world);
	}
}

void Mesh::FixedUpdate(World &world)
{

}


Mesh::~Mesh()
{
}
