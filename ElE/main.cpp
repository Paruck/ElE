#include <SDL\SDL.h>
#include "ElE.h"

int main(int argc, char* argv[])
{
	MotorFlags flag;
	flag.sdl = SDLEverything;
	ElE::App(OpenGL,SDLAudio,PhysX,resizable,flag,500,500);
	return 0;
}