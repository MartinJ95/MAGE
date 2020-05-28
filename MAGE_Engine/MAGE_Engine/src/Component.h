#pragma once

class World;
class Entity;

class Component
{
public:
	Component(Entity &entity);
	virtual void Update(World &world);
	virtual void FixedUpdate(World &world);
	~Component();
	Entity &m_entity;
};

