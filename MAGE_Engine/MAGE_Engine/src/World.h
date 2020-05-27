#pragma once
#include "Visualization.h"

class World
{
public:
	World(const int screenWidth, const int screenHeight, const std::string &windowName);
	bool Initualize();
	void Run();
	~World();
private:
	Visualization m_viz;
};

