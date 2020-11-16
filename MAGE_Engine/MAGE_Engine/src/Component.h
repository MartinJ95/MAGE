#pragma once

class World;
class Entity;
struct collisionData;

class Component
{
public:
	Component(Entity &entity);
	virtual void Update(World &world);
	virtual void FixedUpdate(World &world);
	virtual void onCollisionEnter(World &world, collisionData &data);
	~Component();
	Entity &m_entity;
};

