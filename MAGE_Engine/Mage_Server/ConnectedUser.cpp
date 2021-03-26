#include "ConnectedUser.h"
#include "Server.h"


ConnectedUser::ConnectedUser(Server *server, std::unique_ptr<sf::TcpSocket> socket) :
	serverRef(*server),
	m_socket(std::move(socket)),
	m_buffer(),
	m_bufferSize(sizeof(m_buffer))
{
	//m_socket->setBlocking(false);
}

void ConnectedUser::ReadForMessages()
{
	if (m_socket->receive(&m_buffer, m_bufferSize, m_bufferRecieved) == sf::Socket::Done)
	{
		void *ptr = &m_buffer[0];
		Message m = *static_cast<Message*>(ptr);
		if (m.type == MessageType::PositionUpdate)
		{
			TransformUpdateMessage pm = *static_cast<TransformUpdateMessage*>(ptr);
			serverRef.m_lock.lock();
			for (auto it = serverRef.m_users.begin(); it != serverRef.m_users.end(); it++)
			{
				if (it->first != m.ID)
				{
					it->second->SendMessage(m_buffer, sizeof(pm));
				}
			}
			serverRef.m_lock.unlock();
		}
		else if (m.type == MessageType::Disconnect)
		{
			serverRef.m_lock.lock();
			if (serverRef.m_users.find(m.ID) != serverRef.m_users.end())
			{
				serverRef.m_users.erase(m.ID);
			}
			serverRef.m_lock.unlock();
		}
	}
}

void ConnectedUser::SendMessage(char *message, size_t messageSize)
{
	m_socket->send(message,messageSize);
}

ConnectedUser::~ConnectedUser()
{
	m_socket->disconnect();
}
