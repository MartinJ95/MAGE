#include "ConnectedUser.h"
#include "Server.h"


ConnectedUser::ConnectedUser(Server &server, std::unique_ptr<sf::TcpSocket> socket) :
	serverRef(&server),
	m_socket(std::move(socket))
{
	m_socket->setBlocking(false);
}

void ConnectedUser::ReadForMessages()
{
	if (m_socket->receive(&m_buffer, m_bufferSize, m_bufferRecieved) == sf::Socket::Done)
	{
	}
}

void ConnectedUser::SendMessage()
{
}


ConnectedUser::~ConnectedUser()
{
}
