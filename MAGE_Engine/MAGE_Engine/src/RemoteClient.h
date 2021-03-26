#pragma once
#include "Component.h"
class RemoteClient : 
	public Component
{
public:
	RemoteClient(Entity &entity);
	~RemoteClient();
public:
	int m_ID;
};

