#ifndef RASPBERRY_COMPILE
#include <SDL\SDL.h>
#endif
#include "ElE.h"
#include "ElEDefines.h"

ElEint main(ElEint argc, char* argv[])
{
	MotorFlags flag;
	flag.sdl = SDLEverything;
	ElE::App(OpenGLes20Rasp,SDLAudio,PhysX,resizable,flag,1024,1024,"FUCK YOU");
	return 0;
}
