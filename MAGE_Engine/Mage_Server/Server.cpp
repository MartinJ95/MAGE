#include "Server.h"
#include <thread>



Server::Server() :
	m_listener(new sf::TcpListener),
	m_port(53000)
{
	m_listener->isBlocking = false;
	m_listener->listen(m_port);
}

void Server::run()
{
	while (true)
	{
		m_listenerThread = std::thread(&ListenForConnections, this);

		for (auto it = m_users.begin; it != m_users.end; it++)
		{
			ConnectedUser* user = it->second;
			user->m_ReaderThread = std::thread(&ConnectedUser::ReadForMessages, user);
		}

		m_listenerThread.join();

		for (auto it = m_users.begin; it != m_users.end; it++)
		{
			ConnectedUser* user = it->second;
			user->m_ReaderThread.join();
		}
	}
}

void Server::ListenForConnections()
{
	std::unique_ptr<sf::TcpSocket> newSocket;
	if (m_listener->accept(*newSocket) == sf::Socket::Done)
	{
		for (int i = 0; i < 100; i++)
		{
			if (m_users.find(i) == m_users.end)
			{
				m_users.emplace(std::make_pair(i, new ConnectedUser(*this, std::move(newSocket))));
			}
		}
	}
}


Server::~Server()
{
}
