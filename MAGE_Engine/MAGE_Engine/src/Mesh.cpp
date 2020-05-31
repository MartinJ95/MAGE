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
	Component *t = m_entity.getComponent<Transform>();
	Transform *tran = dynamic_cast<Transform*>(t);
	//world.m_viz.render2D(m_meshName, m_textureName, m_shaderName, (Transform&)t);
	world.m_viz.render2D(m_meshName, m_textureName, m_shaderName, *tran);
}

void Mesh::FixedUpdate(World &world)
{

}


Mesh::~Mesh()
{
}
