#pragma once
#include "Component.h"
class Camera :
	public Component
{
public:
	Camera(Entity &entity);
	void Update(World &world) override;
	void FixedUpdate(World &world) override;
	~Camera();
	float m_fieldOfView;
};

