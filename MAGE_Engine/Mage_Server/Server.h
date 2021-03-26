#include "ConnectedUser.h"
#include "NetworkMessages.h"
#include <unordered_map>
#include <iostream>
#include <thread>
#include <mutex>

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
	bool m_active;
	char m_buffer[1024];
	std::unordered_map<int, ConnectedUser*> m_users;
	std::mutex m_lock;
	std::thread m_listenerThread;
};



