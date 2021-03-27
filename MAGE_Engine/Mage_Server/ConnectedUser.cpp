#include "ConnectedUser.h"
#include "Server.h"


ConnectedUser::ConnectedUser(Server *server, std::unique_ptr<sf::TcpSocket> socket) :
	serverRef(*server),
	m_socket(std::move(socket)),
	m_buffer(),
	m_connected(true),
	m_bufferSize(sizeof(m_buffer)),
	m_lock()
{
	//m_socket->setBlocking(false);
	m_ReaderThread = std::thread(&ConnectedUser::ReadForMessages, this);
}

void ConnectedUser::ReadForMessages()
{
	while (m_connected)
	{
		if (m_socket->receive(&m_buffer, m_bufferSize, m_bufferRecieved) == sf::Socket::Done)
		{
			serverRef.m_lock.lock();
			void *ptr = &m_buffer[0];
			Message m = *static_cast<Message*>(ptr);
			if (m.type == MessageType::PositionUpdate)
			{
				//TransformUpdateMessage pm = *static_cast<TransformUpdateMessage*>(ptr);
				TransformUpdateMessage *pm = static_cast<TransformUpdateMessage*>(ptr);
				std::cout << pm->position.x << "." << pm->position.y << "." << pm->position.z << std::endl;
				std::cout << m_bufferRecieved << std::endl;
				if (serverRef.m_users.find(pm->ID) != serverRef.m_users.end())
				{
					for (auto it = serverRef.m_users.begin(); it != serverRef.m_users.end(); it++)
					{
						if (it->first != pm->ID)
						{
							it->second->SendMessage(m_buffer, sizeof(TransformUpdateMessage));
						}
					}
				}
				
			}
			else if (m.type == MessageType::Disconnect)
			{
				serverRef.m_lock.lock();
				if (serverRef.m_users.find(m.ID) != serverRef.m_users.end())
				{
					serverRef.m_users.erase(m.ID);
				}
			}
			serverRef.m_lock.unlock();
		}
	}
}

void ConnectedUser::SendMessage(void *message, size_t messageSize)
{
	m_lock.lock();
	m_socket->send(message,messageSize);
	m_lock.unlock();
}

ConnectedUser::~ConnectedUser()
{
	m_socket->disconnect();
}
