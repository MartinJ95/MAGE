#include "NetworkClient.h"
#include "World.h"

NetworkClient::NetworkClient(World &world) :
	m_socket(),
	m_ID(-1),
	m_buffer(),
	m_bufferSize(sizeof(m_buffer)),
	m_worldRef(world)
{
	sf::IpAddress ipAddress;
	std::cout << "enter ipAddress the server is running on" << std::endl;
	std::cin >> ipAddress;
	std::cout << "address : " << ipAddress << std::endl;
	if (m_socket.connect(ipAddress, port, sf::seconds(5)) == sf::Socket::Status::Done)
	{
		std::cout << "connected to server" << std::endl;
		RecieveMessage();
	}
	else
	{
		std::cout << "failed to connect" << std::endl;
	}
}

void NetworkClient::RecieveMessage()
{
	if (m_socket.receive(m_buffer, m_bufferSize, m_bufferRecieved) == sf::Socket::Done)
	{
		void *ptr = &m_buffer[0];
		Message m = *static_cast<Message*>(ptr);
		if (m.type == Connect)
		{
			if (m_ID == -1)
			{
				m_socket.setBlocking(false);
				m_ID = m.ID;
			}
			else if (m.ID > 0)
			{
				for (int i = 0; i < m_worldRef.m_entities.size(); i++)
				{
					if (m_worldRef.m_entities[i]->m_active == false && m_worldRef.m_entities[i]->getComponent<RemoteClient>() != NULL)
					{
						m_worldRef.m_entities[i]->m_active = true;
						m_worldRef.m_entities[i]->getComponent<RemoteClient>()->m_ID = m.ID;
						break;
					}
				}
			}
		}
		else if (m.type == MessageType::Disconnect)
		{
			for (int i = 0; i < m_worldRef.m_entities.size(); i++)
			{
				if (m_worldRef.m_entities[i]->m_active = true && m_worldRef.m_entities[i]->getComponent<RemoteClient>() != NULL)
				{
					if (m_worldRef.m_entities[i]->getComponent<RemoteClient>()->m_ID == m.ID)
					{
						m_worldRef.m_entities[i]->getComponent<RemoteClient>()->m_ID = -1;
						m_worldRef.m_entities[i]->m_active = false;
					}
				}
			}
		}
		else if (m.type == MessageType::PositionUpdate)
		{
			TransformUpdateMessage *tm = (TransformUpdateMessage*)&m;
			for (int i = 0; i < m_worldRef.m_entities.size(); i++)
			{
				if (m_worldRef.m_entities[i]->m_active = true && m_worldRef.m_entities[i]->getComponent<RemoteClient>() != NULL)
				{
					if (m_worldRef.m_entities[i]->getComponent<RemoteClient>()->m_ID == m.ID)
					{
						m_worldRef.m_entities[i]->getComponent<Transform>()->m_position = tm->position;
						m_worldRef.m_entities[i]->getComponent<Transform>()->m_rotation = tm->rotation;
						m_worldRef.m_entities[i]->getComponent<Transform>()->m_scale = tm->scale;
					}
				}
			}
		}
	}
}

void NetworkClient::SendMessage(const Message *message)
{
	if (message->type == MessageType::PositionUpdate)
	{
		TransformUpdateMessage *m = (TransformUpdateMessage*)message;
		m_socket.send(m, sizeof(m), m_bufferSize);
	}
	else if (message->type == MessageType::Disconnect)
	{
		m_socket.send(message, sizeof(message), m_bufferSize);
	}
}

NetworkClient::~NetworkClient()
{
	Message m;
	m.type = MessageType::Disconnect;
	m.ID = m_ID;
	m_socket.send(&m, sizeof(m), m_bufferSize);
	m_socket.disconnect();
}
