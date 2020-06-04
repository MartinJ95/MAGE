#include "Camera.h"



Camera::Camera(Entity &entity) :
	Component(entity),
	m_fieldOfView(45)
{
}

void Camera::Update(World &world)
{

}

void Camera::FixedUpdate(World &world)
{

}

Camera::~Camera()
{
}
