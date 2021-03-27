#pragma once
#include "Component.h"
class RemoteClient : 
	public Component
{
public:
	RemoteClient(Entity &entity);
	void Update(World &world) override;
	~RemoteClient();
public:
	int m_ID;
};

