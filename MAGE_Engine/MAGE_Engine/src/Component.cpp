#include "Component.h"
#include "World.h"
#include "Entity.h"


Component::Component(Entity &entity) :
	m_entity(entity)
{
}

void Component::Update(World &world)
{
}

void Component::FixedUpdate(World &world)
{
}

Component::~Component()
{
	
}
