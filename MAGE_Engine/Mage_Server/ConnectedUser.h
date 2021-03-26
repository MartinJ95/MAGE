#include <SFML/Network.hpp>
#include <thread>

class Server;

#pragma once
class ConnectedUser
{
public:
	ConnectedUser(Server *server, std::unique_ptr<sf::TcpSocket> socket);
	void ReadForMessages();
	void SendMessage(char *message, size_t messageSize);
	~ConnectedUser();
public:
	Server &serverRef;
	std::unique_ptr<sf::TcpSocket> m_socket;
	sf::IpAddress m_address;
	char m_buffer[1024];
	size_t m_bufferSize;
	size_t m_bufferRecieved;
	std::thread m_ReaderThread;
};

