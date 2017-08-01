#include <SDL\SDL.h>
#include "ElE.h"
#include "ElEDefines.h"

ElEint main(ElEint argc, char* argv[])
{
	MotorFlags flag;
	flag.sdl = SDLEverything;
	ElE::App(OpenGL,SDLAudio,PhysX,resizable | openGL,flag,500,500,"FUCK YOU");
	return 0;
}