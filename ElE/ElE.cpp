#include "ElE.h"
#include "ElEMainScene.h"

ElEGraphicsComponents					ElE::graphicsComp;
ElEAudioComponents						ElE::audioComp;
ElEPhysicsComponents					ElE::physicsComp;
ElEint									ElE::setFlags;
ElEuint									ElE::screenWidth,
										ElE::screenHeight;
MotorFlags								ElE::motorFlags;
ElEWindow*								ElE::window;
ElERender*								ElE::render;
ElESurface*								ElE::surface;
ElETexture*								ElE::texture;
std::vector<void(*)()>					ElE::initFunctions;
ElEchar*								ElE::windowTitle;
ElEGLContext*                           ElE::context;
#ifndef RASPBERRY_COMPILE
SDL_Event								ElE::event;
#else
EGLStuff                                ElE::stuff;
GLMeshIDManager                         ElE::mngr;
#endif
void ElE::App(
	const _IN_ ElEGraphicsComponents & graph,
	const _IN_ ElEAudioComponents & audio,
	const _IN_ ElEPhysicsComponents & phys,
	const _IN_ ElEint & flags,
	const _IN_ MotorFlags & mFlags,
	const _IN_ ElEuint & width,
	const _IN_ ElEuint & height,
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
	#ifndef RASPBERRY_COMPILE
		PollEvents();
		if (event.type == SDL_QUIT) exit(0);
		SDL_RenderClear(render->render.sdlRender);
		SDL_RenderPresent(render->render.sdlRender);
    #endif
		ElESceneManager::getInstance()->SceneMainLoop();
	}
}

void ElE::PrepareJumpTables()
{
	initFunctions.push_back(ElE::InitSFML);
	initFunctions.push_back(ElE::InitSDL);
	initFunctions.push_back(ElE::InitVulkan);
	initFunctions.push_back(ElE::InitOpenGLes20Rasp);
	initFunctions.push_back(ElE::InitCDM);
}

void ElE::InitSFML()
{
#ifndef RASPBERRY_COMPILE
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
		#endif
}

void ElE::InitSDL()
{
#ifndef RASPBERRY_COMPILE
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
	#endif
}

void ElE::InitVulkan()
{
	printf("oiie papu, vulkan inicio\n");
}

void ElE::InitCDM()
{

}

#define RASPBERRY_COMPILE
void ElE::InitOpenGLes20Rasp()
{
#ifdef RASPBERRY_COMPILE
	bcm_host_init();
	EGLBoolean                      result;

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
    context = new ElEGLContext(graphicsComp);
	EGLConfig config;
	render->render.eglRender = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	assert(render->render.eglRender != EGL_NO_DISPLAY);

	result = eglInitialize(render->render.eglRender, NULL, NULL);
	assert(result != EGL_FALSE);

    result = eglChooseConfig(render->render.eglRender, attribute_list, &config, 1, &stuff.num_config);
	assert(result != EGL_FALSE);

	result = eglBindAPI(EGL_OPENGL_ES_API);
	assert(result != EGL_FALSE);

	context->context.EGLcontext = eglCreateContext(render->render.eglRender, config,
        EGL_NO_CONTEXT, context_attributes);
	assert(context != EGL_NO_CONTEXT);

	stuff.success = graphics_get_display_size(0, &screenWidth, &screenHeight);
	assert(stuff.success >= 0);

	stuff.dst_rect.x = 0;
	stuff.dst_rect.y = 0;
	stuff.dst_rect.width = screenWidth;
	stuff.dst_rect.height = screenHeight;

	stuff.src_rect.x = 0;
	stuff.src_rect.y = 0;
	stuff.src_rect.width = screenWidth << 16;
	stuff.src_rect.height = screenHeight << 16;

	stuff.dispman_display = vc_dispmanx_display_open(0);
	stuff.dispman_update = vc_dispmanx_update_start(0);

	stuff.dispman_element = vc_dispmanx_element_add(
		stuff.dispman_update, stuff.dispman_display, 0,
		&stuff.dst_rect, 0, &stuff.src_rect,
		DISPMANX_PROTECTION_NONE, 0, 0,
		(DISPMANX_TRANSFORM_T)0);

	stuff.nativeWindow.element = stuff.dispman_element;
	stuff.nativeWindow.width = screenWidth;
	stuff.nativeWindow.height = screenHeight;
	vc_dispmanx_update_submit_sync(stuff.dispman_update);

	window->window.eglWindow = &stuff.nativeWindow;
	surface->surface.eglSurface = eglCreateWindowSurface(render->render.eglRender, config,
		window->window.eglWindow, NULL);
	assert(surface->surface.eglSurface != EGL_NO_SURFACE);

	result = eglMakeCurrent(render->render.eglRender, surface->surface.eglSurface,
	 surface->surface.eglSurface, context->context.EGLcontext);
	assert(result != EGL_FALSE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, screenWidth, screenHeight);
	eglSwapBuffers(render->render.eglRender, surface->surface.eglSurface);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_SCISSOR_TEST);
	std::cout << "OpenGLes initialized" << std::endl;
#endif
}

void ElE::Init()
{
	render = new ElERender(graphicsComp);
	surface = new ElESurface(graphicsComp);
	window = new ElEWindow(graphicsComp);
	texture = new ElETexture(graphicsComp);
	(initFunctions.at(graphicsComp))();
}

void ElE::PollEvents()
{
	//cambiar por tabla de salto
	switch (graphicsComp)
	{
#ifndef RASPBERRY_COMPILE
	case SDLGraphics:
		SDL_PollEvent(&event);
	break;
#else
    case OpenGLes20Rasp:
        break;
#endif
	}
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
#ifndef RASPBERRY_COMPILE
	case OpenGL:
		window.sfmlWindow = nullptr;
		break;
	case SDLGraphics:
		window.sdlWindow = nullptr;
		break;
#endif
	case OpenGLes20Rasp:
		window.eglWindow = nullptr;
		break;
	}
}

ElEWindow::~ElEWindow()
{
	switch (type)
	{
	#ifndef RASPBERRY_COMPILE
	case SDLGraphics:
		SDL_DestroyWindow(window.sdlWindow);
		break;
    #endif
	}
}

ElESurface::ElESurface(const ElEGraphicsComponents & renderT)
{
	type = renderT;
	switch (renderT)
	{
	#ifndef RASPBERRY_COMPILE
	case SDLGraphics:
		surface.sdlSurface = nullptr;
		break;
    #endif
	}
}

ElESurface::~ElESurface()
{
	switch (type)
	{
	#ifndef RASPBERRY_COMPILE
	case SDLGraphics:
		SDL_FreeSurface(surface.sdlSurface);
		break;
    #endif
	}
}

ElETexture::ElETexture(const ElEGraphicsComponents & renderT)
{
	type = renderT;
	switch (renderT)
	{
	#ifndef RASPBERRY_COMPILE
	case SDLGraphics:
		texture.sdlTexture = nullptr;
		break;
		#endif
	}
}

ElETexture::~ElETexture()
{
	switch (type)
	{
	#ifndef RASPBERRY_COMPILE
	case SDLGraphics:
		SDL_DestroyTexture(texture.sdlTexture);
		break;
		#endif
	}
}

ElERender::ElERender(const ElEGraphicsComponents & renderT)
{
	type = renderT;
	switch (renderT)
	{
	#ifndef RASPBERRY_COMPILE
	case SDLGraphics:
		render.sdlRender = nullptr;
		break;
		#endif
	}
}

ElERender::~ElERender()
{
	switch (type)
	{
	#ifndef RASPBERRY_COMPILE
	case SDLGraphics:
		SDL_DestroyRenderer(render.sdlRender);
		break;
		#endif
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

GLMeshIDManager::GLMeshIDManager()
{
    data = new struct Sdata[GL_MAX_VERTEX_ATTRIBS-1];
    for(ElEuint i = GL_MAX_VERTEX_ATTRIBS; i--;)
        data[i].id = i;
}

ElEuint GLMeshIDManager::getUnusedID()
{
    for(ElEuint i = GL_MAX_VERTEX_ATTRIBS; i--;)
    {
        if(!data[i].inUse)
        {
            data[i].inUse = ElEtrue;
            return data[i].id;
        }
    }
    return -1;
}

ElEvoid GLMeshIDManager::cleanUsedID(ElEuint idTag)
{
    data[idTag].inUse = ElEfalse;
}
