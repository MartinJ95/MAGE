#pragma once
#include "Maths.h"

enum MessageType
{
	Connect = 0,
	Disconnect = 1,
	PositionUpdate = 2
};

struct Message
{
	MessageType type;
	int ID;
};

struct DirectionChangeMessage : Message
{

};

struct TransformUpdateMessage : Message
{
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
};