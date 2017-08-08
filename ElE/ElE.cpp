#include "ElE.h"
#include "ElEMainScene.h"

ElEGraphicsComponents					ElE::graphicsComp;
ElEAudioComponents						ElE::audioComp;
ElEPhysicsComponents					ElE::physicsComp;
ElEint									ElE::setFlags,
										ElE::screenWidth,
										ElE::screenHeight;
MotorFlags								ElE::motorFlags;
ElEWindow*								ElE::window;
ElERender*								ElE::render;
ElESurface*								ElE::surface;
ElETexture*								ElE::texture;
ElEVector<std::function<void()>>		ElE::initFunctions;
ElEchar*								ElE::windowTitle;
SDL_Event								ElE::event;

void ElE::App(
	const _IN_ ElEGraphicsComponents & graph,
	const _IN_ ElEAudioComponents & audio,
	const _IN_ ElEPhysicsComponents & phys,
	const _IN_ ElEint & flags,
	const _IN_ MotorFlags & mFlags,
	const _IN_ ElEint & width,
	const _IN_ ElEint & height,
	_IN_ ElEchar* title)
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
	ElEThreadPool::getInstance(threadAmmount);
	ElESceneManager::getInstance()->ChangeScene(new ElEMainScene());
	while (1)
	{
		PollEvents();
		if (event.type == SDL_QUIT) exit(0);
		SDL_RenderClear(render->render.sdlRender);
		ElESceneManager::getInstance()->SceneMainLoop();
		SDL_RenderPresent(render->render.sdlRender);
	}
}

void ElE::PrepareJumpTables()
{
	initFunctions.add(ElE::InitSFML);
	initFunctions.add(ElE::InitSDL);
	initFunctions.add(ElE::InitVulkan);
	initFunctions.add(ElE::InitCDM);
	initFunctions.add(ElE::InitOpenGLes20Rasp);
}

void ElE::InitSFML()
{
	window = new ElEWindow(graphicsComp);
	ElEint f = 0;
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
	const ElEint flags = MIX_INIT_FLAC |
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
	const ElEint flagsI = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if ((IMG_Init(flagsI) & flagsI) != flagsI)
	{
		SDL_Log("Failed to initialize Image Library: %s", IMG_GetError());
		exit(-8);
	}
	Mix_VolumeMusic(100);
	SDL_SetRenderDrawColor(render->render.sdlRender, 0, 0, 0, 255);
}

void ElE::InitVulkan()
{
	printf("oiie papu, vulkan inicio\n");
}

void ElE::InitCDM()
{

}

void ElE::InitOpenGLes20Rasp()
{
#ifdef RASPBERRY_COMPILE
	bcm_host_init();

	static EGL_DISPMANX_WINDOW_T 	nativeWindow;
	DISPMANX_ELEMENT_HANDLE_T	dispman_element;
	DISPMANX_DISPLAY_HANDLE_T	dispman_display;
	DISPMANX_UPDATE_HANDLE_T	dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;
	static const EGLint attribute_list[] =
	{
		EGL_RED_SIZE, 		8,
		EGL_GREEN_SIZE, 	8,
		EGL_BLUE_SIZE,		8,
		EGL_ALPHA_SIZE,		8,
		EGL_DEPTH_SIZE,		16,
		EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
		EGL_NONE
	};

	static const EGLint context_attributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION,	2,
		EGL_NONE
	};

	EGLConfig config;
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	assert(display != EGL_NO_DISPLAY);

	result = eglInitialize(display, NULL, NULL);
	assert(result != EGL_FALSE);

	result = eglChooseConfig(display, attribute_list, &config, 1, &num_config);
	assert(result != EGL_FALSE);

	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(result != EGL_FALSE);

	context = eglCreateContext(display, config,
		EGL_NO_CONTEXT, context_attributes);
	assert(context != EGL_NO_CONTEXT);

	success = graphics_get_display_size(0, &screenWidth, &screenHeight);
	assert(success >= 0);

	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width = screenWidth;
	dst_rect.height = screenHeight;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = screenWidth << 16;
	src_rect.height = screenHeight << 16;

	dispman_display = vc_dispmanx_display_open(0);
	dispman_update = vc_dispmanx_update_start(0);

	dispman_element = vc_dispmanx_element_add(
		dispman_update, dispman_display, 0,
		&dst_rect, 0, &src_rect,
		DISPMANX_PROTECTION_NONE, 0, 0,
		(DISPMANX_TRANSFORM_T)0);

	nativeWindow.element = dispman_element;
	nativeWindow.width = screenWidth;
	nativeWindow.height = screenHeight;
	vc_dispmanx_update_submit_sync(dispman_update);

	hWnd = &nativeWindow;
	surface = eglCreateWindowSurface(display, config,
		hWnd, NULL);
	assert(surface != EGL_NO_SURFACE);

	result = eglMakeCurrent(display, surface, surface, context);
	assert(result != EGL_FALSE);

	glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, screenWidth, screenHeight);
	eglSwapBuffers(display, surface);
	glEnable(GL_TEXTURE_2D);
	std::cout << "OpenGLes initialized" << std::endl;
#endif
}

void ElE::Init()
{
	render = new ElERender(graphicsComp);
	surface = new ElESurface(graphicsComp);
	window = new ElEWindow(graphicsComp);
	texture = new ElETexture(graphicsComp);
	(*initFunctions.at(graphicsComp))();
}

void ElE::PollEvents()
{
	//cambiar por tabla de salto
#ifndef RASPBERRY_COMPILE
	switch (graphicsComp)
	{
	case SDLGraphics:
		SDL_PollEvent(&event);
	break;
	}
#endif
}

#ifdef RASPBERRY_COMPILE
void ElE::InitGLesPlane()
{

}
#endif

ElE::ElE()
{
}

ElE::~ElE()
{
}

ElEWindow::ElEWindow(const ElEGraphicsComponents & renderT)
{
	type = renderT;
	switch (renderT)
	{
	case OpenGL:
		window.sfmlWindow = nullptr;
		break;
	case OpenGLes20Rasp:
#ifdef RASPBERRY_COMPILE
		window.eglWindow = nullptr;
#endif 
		break;
	case SDLGraphics:
		window.sdlWindow = nullptr;
		break;
	}
}

ElEWindow::~ElEWindow()
{
	switch (type)
	{
	case SDLGraphics:
		SDL_DestroyWindow(window.sdlWindow);
		break;
	}
}

ElESurface::ElESurface(const ElEGraphicsComponents & renderT)
{
	type = renderT;
	switch (renderT)
	{
	case SDLGraphics:
		surface.sdlSurface = nullptr;
		break;
	}
}

ElESurface::~ElESurface()
{
	switch (type)
	{
	case SDLGraphics:
		SDL_FreeSurface(surface.sdlSurface);
		break;
	}
}

ElETexture::ElETexture(const ElEGraphicsComponents & renderT)
{
	type = renderT;
	switch (renderT)
	{
	case SDLGraphics:
		texture.sdlTexture = nullptr;
		break;
	}
}

ElETexture::~ElETexture()
{
	switch (type)
	{
	case SDLGraphics:
		SDL_DestroyTexture(texture.sdlTexture);
		break;
	}
}

ElERender::ElERender(const ElEGraphicsComponents & renderT)
{
	type = renderT;
	switch (renderT)
	{
	case SDLGraphics:
		render.sdlRender = nullptr;
		break;
	}
}

ElERender::~ElERender()
{
	switch (type)
	{
	case SDLGraphics:
		SDL_DestroyRenderer(render.sdlRender);
		break;
	}
}

ElEGLContext::ElEGLContext(const ElEGraphicsComponents & renderT)
{
	type = renderT;
}

ElEGLContext::~ElEGLContext()
{
	switch (type)
	{

	}
}

