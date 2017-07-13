#include "ElE.h"

ElEGraphicsComponents					ElE::graphicsComp;
ElEAudioComponents						ElE::audioComp;
ElEPhysicsComponents					ElE::physicsComp;
int										ElE::setFlags;
MotorFlags								ElE::motorFlags;
ElEWindow*								ElE::window;
ElERender*								ElE::render;
ElESurface*								ElE::surface;
ElETexture*								ElE::texture;
std::vector<std::function<void()>>		ElE::initFunctions;
int										ElE::screenWidth,
										ElE::screenHeight;
char*									ElE::windowTitle;

void ElE::App(
	const _IN_ ElEGraphicsComponents & graph,
	const _IN_ ElEAudioComponents & audio,
	const _IN_ ElEPhysicsComponents & phys,
	const _IN_ int & flags,
	const _IN_ MotorFlags & mFlags,
	const _IN_ int & width,
	const _IN_ int & height,
	_IN_ char* title)
{
	graphicsComp = graph;
	audioComp = audio;
	physicsComp = phys;
	setFlags = flags;
	screenWidth = width;
	screenHeight = height;
	motorFlags = mFlags;
	windowTitle = title;
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
	window = new ElEWindow(graphicsComp);
	int f = 0;
	if (setFlags & none)
		f |= sf::Style::None;
	if (setFlags & titleBar)
		f |= sf::Style::Titlebar;
	if (setFlags & resizable)
		f |= sf::Style::Resize;
	if (setFlags & closeButton)
		f |= sf::Style::Close;
	if (setFlags & fullScreen)
		f |= sf::Style::Fullscreen;
	if (setFlags & autoFlagsW)
		f |= sf::Style::Default;
	if (setFlags & openGL)
	{
		sf::ContextSettings set;
		set.depthBits = 24;
		set.stencilBits = 8;
		set.sRgbCapable = true;
		set.antialiasingLevel = 4;
		set.minorVersion = 3;
		set.majorVersion = 4;
		window->window.sfmlWindow = new sf::Window(sf::VideoMode(screenWidth, screenHeight), windowTitle, f, set);
	}
	else
		window->window.sfmlWindow = new sf::Window(sf::VideoMode(screenWidth, screenHeight), windowTitle, f);
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
	if (SDL_CreateWindowAndRenderer(screenWidth, screenHeight, motorFlags.sdl, &window->window.sdlWindow, &render->render.sdlRender) == -1)
	{
		SDL_Log("Failed to initialize Window: %s", SDL_GetError());
		exit(-2);
	}
	SDL_SetWindowTitle(window->window.sdlWindow, windowTitle);
	surface->surface.sdlSurface = SDL_GetWindowSurface(window->window.sdlWindow);
	texture->texture.sdlTexture = SDL_CreateTextureFromSurface(render->render.sdlRender, surface->surface.sdlSurface);
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

ElEWindow::ElEWindow(const ElEGraphicsComponents & renderT)
{
	if (renderT == OpenGL)
		window.sfmlWindow = nullptr;
}

ElEWindow::~ElEWindow()
{
}

ElESurface::ElESurface(const ElEGraphicsComponents & renderT)
{
}

ElESurface::~ElESurface()
{
}

ElETexture::ElETexture(const ElEGraphicsComponents & renderT)
{
}

ElETexture::~ElETexture()
{
}

ElERender::ElERender(const ElEGraphicsComponents & renderT)
{
}

ElERender::~ElERender()
{
}
