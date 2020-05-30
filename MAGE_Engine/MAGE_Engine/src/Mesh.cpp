#include "Mesh.h"
#include "World.h"
#include "Entity.h"


Mesh::Mesh(Entity &entity) :
	Component(entity),
	m_meshName(),
	m_textureName()
{
}

void Mesh::Update(World &world)
{

}

void Mesh::FixedUpdate(World &world)
{

}


Mesh::~Mesh()
{
}
