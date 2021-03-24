#include "World.h"
#include "Maths.h"
#include <iostream>

int main(void)
{
	World world(640, 480, "MAGE");

	if (!world.Initualize())
	{
		return -1;
	}
	world.Run();

	return 0;
}