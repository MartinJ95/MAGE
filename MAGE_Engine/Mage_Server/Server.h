#include "ConnectedUser.h"
#include <unordered_map>
#include <iostream>

constexpr unsigned short serverPort = 53000;

#pragma once
class Server
{
public:
	Server();
	void run();
	void ListenForConnections();
	~Server();
public:
	sf::TcpListener *m_listener;
	const unsigned short m_port;
	std::unordered_map<int, ConnectedUser> m_users;
	std::thread m_listenerThread;
};

