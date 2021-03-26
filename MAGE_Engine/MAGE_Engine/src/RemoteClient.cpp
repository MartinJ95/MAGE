#include "RemoteClient.h"



RemoteClient::RemoteClient(Entity &entity) : 
	Component(entity),
	m_ID(-1)
{
}


RemoteClient::~RemoteClient()
{
}
