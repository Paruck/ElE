#include "ElE.h"



void ElE::App(const ElEGraphicsComponents& graph,
	const ElEAudioComponents& audio,
	const ElEPhysicsComponents& phys,
	const Flags& flags,
	const int& width,
	const int& height)
{
	Init(flags);
	printf("Presiona enter para continuar\n");
	while (1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			break;
	}
}

void ElE::Init(const Flags& flags)
{
}

ElE::ElE()
{
}


ElE::~ElE()
{
}
