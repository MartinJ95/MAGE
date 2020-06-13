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
	void updateDirection();
	void updateRotation(World &world);
	void snapRotation(Vector3f &rotation);
	void applyEulerToForward(const Vector3f &rotation, Vector3f &forward);
	Vector3f worldForward();
	Vector3f worldPosition();
	Vector3f worldScale();
	Vector3f worldRotation();
	~Transform();
	Vector3f m_forward;
	Vector3f m_position;
	Vector3f m_scale;
	Vector3f m_rotation; //(vec3(pitch, yaw, roll))
};

