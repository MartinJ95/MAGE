#include "Server.h"

Server::Server() :
	m_listener(new sf::TcpListener),
	m_port(53000),
	m_active(true),
	m_lock()
{
	//m_listener->setBlocking(false);
	if (m_listener->listen(m_port) != sf::Socket::Done)
	{
		std::cout << "can't listen" << std::endl;
	}
	
	std::cout << "server is active, public IP : " << sf::IpAddress::getPublicAddress(sf::seconds(5)) << std::endl;
	std::cout << "local ip : " << sf::IpAddress::getLocalAddress() << std::endl;

}

void Server::run()
{
	m_listenerThread = std::thread(&Server::ListenForConnections, this);
	while (true)
	{
		/*for (auto it = m_users.begin(); it != m_users.end(); it++)
		{
			ConnectedUser* user = it->second;
			user->m_ReaderThread = std::thread(&ConnectedUser::ReadForMessages, user);
		}
		for (auto it = m_users.begin(); it != m_users.end(); it++)
		{
			ConnectedUser* user = it->second;
			if (user->m_ReaderThread.joinable())
			{
				user->m_ReaderThread.join();
			}
		}*/
	}
}

void Server::ListenForConnections()
{
	while (m_active)
	{
		std::cout << "listening" << std::endl;
		std::unique_ptr<sf::TcpSocket> newSocket = std::make_unique<sf::TcpSocket>();
		if (m_listener->accept(*newSocket) == sf::Socket::Done)
		{
			std::cout << "accepting new client" << std::endl;
			for (int i = 0; i < 100; i++)
			{
				m_lock.lock();
				if (m_users.find(i) == m_users.end())
				{
					newSocket->setBlocking(false);
					std::cout << "confirming new client" << std::endl;
					m_users.emplace(std::make_pair(i, new ConnectedUser(this, std::move(newSocket))));
					Message newMessage;
					newMessage.type = Connect;
					newMessage.ID = i;
					for (auto it = m_users.begin(); it != m_users.end(); it++)
					{
						char *message = (char*)&newMessage;
						it->second->SendMessage(message, sizeof(Message));
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
					for (auto it = m_users.begin(); it != m_users.end(); it++)
					{
						if (it->first != i)
						{
							Message previousConnected;
							previousConnected.type = Connect;
							previousConnected.ID = it->first;
							m_users.find(i)->second->SendMessage(&previousConnected, sizeof(Message));
						}
					}
					m_lock.unlock();
					break;
				}
				m_lock.unlock();
			}
		}
	}
}


Server::~Server()
{
	m_active = false;
	m_listener->close();
	m_listenerThread.join();
}
