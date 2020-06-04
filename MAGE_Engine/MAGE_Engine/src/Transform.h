#pragma once
#include "Component.h"
#include "Maths.h"

class Entity;
class World;

class Transform :
	public Component
{
public:
	Transform(Entity &entity);
	void Update(World &world) override;
	void FixedUpdate(World &world) override;
	~Transform();
	Vector3f m_forward;
	Vector3f m_position;
	Vector3f m_scale;
	Vector3f m_rotation; //(vec3(yaw, pitch, roll))
};

