#pragma once

class World;

class Component
{
public:
	Component();
	void Update(World &world);
	void FixedUpdate();
	~Component();
};

