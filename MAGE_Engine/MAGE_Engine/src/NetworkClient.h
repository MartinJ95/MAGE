#pragma once
#include <SFML/Network.hpp>
#include "NetworkMessages.h"
#include <iostream>

class World;

const unsigned short port = 53000;

class NetworkClient
{
public:
	sf::TcpSocket m_socket;
	int m_ID;
	char m_buffer[1024];
	size_t m_bufferSize;
	size_t m_bufferRecieved;
	World &m_worldRef;
	NetworkClient(World &world);
	void RecieveMessage();
	void SendMessage(const Message *message);
	~NetworkClient();
};

