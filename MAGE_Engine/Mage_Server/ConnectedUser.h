#include <SFML/Network.hpp>
#include <thread>
#include <mutex>

class Server;

#pragma once
class ConnectedUser
{
public:
	ConnectedUser(Server *server, std::unique_ptr<sf::TcpSocket> socket);
	void ReadForMessages();
	void SendMessage(void *message, size_t messageSize);
	~ConnectedUser();
public:
	Server &serverRef;
	std::unique_ptr<sf::TcpSocket> m_socket;
	sf::IpAddress m_address;
	char m_buffer[1024];
	size_t m_bufferSize;
	size_t m_bufferRecieved;
	bool m_connected;
	std::thread m_ReaderThread;
	std::mutex m_lock;
};

