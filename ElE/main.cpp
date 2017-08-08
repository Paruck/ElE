#include <SDL\SDL.h>
#include "ElE.h"
#include "ElEDefines.h"

ElEint main(ElEint argc, char* argv[])
{
	MotorFlags flag;
	flag.sdl = SDLEverything;
	ElE::App(SDLGraphics,SDLAudio,PhysX,resizable,flag,1024,1024,"FUCK YOU");
	return 0;
}