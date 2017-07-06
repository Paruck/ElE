#include "ElE.h"

ElEGraphicsComponents					ElE::graphicsComp;
ElEAudioComponents						ElE::audioComp;
ElEPhysicsComponents					ElE::physicsComp;
WindowFlags								ElE::setFlags;
MotorFlags								ElE::motorFlags;
ElEWindow								ElE::window;
ElERender								ElE::render;
ElESurface								ElE::surface;
ElETexture								ElE::texture;
std::vector<std::function<void()>>		ElE::initFunctions;
int										ElE::screenWidth,
										ElE::screenHeight;

void ElE::App(
	const _IN_ ElEGraphicsComponents & graph,
	const _IN_ ElEAudioComponents & audio,
	const _IN_ ElEPhysicsComponents & phys,
	const _IN_ WindowFlags & flags,
	const _IN_ MotorFlags & mFlags,
	const _IN_ int & width,
	const _IN_ int & height)
{
	graphicsComp = graph;
	audioComp = audio;
	physicsComp = phys;
	setFlags = flags;
	screenWidth = width;
	screenHeight = height;
	motorFlags = mFlags;
	PrepareJumpTables();
	Init();
	printf("Presiona enter para continuar\n");
	while (1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			break;
	}
}

void ElE::PrepareJumpTables()
{
	initFunctions.push_back(ElE::InitSFML);
	initFunctions.push_back(ElE::InitSDL);
	initFunctions.push_back(ElE::InitVulkan);
	initFunctions.push_back(ElE::InitCDM);
}

void ElE::InitSFML()
{
}

void ElE::InitSDL()
{
	//Inicializaciones, SDL se encarga de detectar la plataforma 
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//Manejo de errores criticos, cierra la aplicacion al encontrar un error
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		exit(-1);
	}
	//Se encarga de comprobar si al inicializar la escenas hay un error 
	if (SDL_CreateWindowAndRenderer(screenWidth, screenHeight, motorFlags.sdl, &window.sdlWindow, &render.sdlRender) == -1)
	{
		SDL_Log("Failed to initialize Window: %s", SDL_GetError());
		exit(-2);
	}
	surface.sdlSurface = SDL_GetWindowSurface(window.sdlWindow);
	texture.sdlTexture = SDL_CreateTextureFromSurface(render.sdlRender, surface.sdlSurface);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(-5);
	}
	const int flags = MIX_INIT_FLAC |
		MIX_INIT_MP3 |
		MIX_INIT_OGG;
	if ((Mix_Init(flags) & flags) != flags)
	{
		SDL_Log("Failed to initialize audio library.");
		exit(-6);
	}
	if (TTF_Init() == -1)
	{
		SDL_Log("TTF failed to initialize.");
		exit(-7);
	}
	const int flagsI = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if ((IMG_Init(flagsI) & flagsI) != flagsI)
	{
		SDL_Log("Failed to initialize Image Library: %s", IMG_GetError());
		exit(-8);
	}
	Mix_VolumeMusic(100);
}

void ElE::InitVulkan()
{
	printf("oiie papu, vulkan inicio\n");
}

void ElE::InitCDM()
{
}

void ElE::Init()
{
	initFunctions[graphicsComp]();
}

ElE::ElE()
{
}


ElE::~ElE()
{
}
