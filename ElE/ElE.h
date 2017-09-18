#pragma once
//#define RASPBERRY_COMPILE

#include "ElEVector.h"
#include "ElEDefines.h"
#include "ElEThread.h"
#include "ElESceneManager.h"

#ifndef RASPBERRY_COMPILE
#include <SDL\SDL.h>
#include <SFML\Main.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SDL\SDL_ttf.h>
#include <SDL\SDL_mixer.h>
#include <SDL\SDL_image.h>

#else
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "bcm_host.h"

#endif

#include <functional>
#include <string.h>
#include <math.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <vector>

#define RASPBERRY_COMPILE
class ElEGLContext {
public:
	union Context {
#ifdef RASPBERRY_COMPILE
		EGLContext				EGLcontext;
#endif
	}context;
	ElEGLContext() = delete;
	ElEGLContext(const ElEGraphicsComponents& renderT);
	~ElEGLContext();
private:
	ElEGraphicsComponents type;
};

class ElEWindow
{
public:
	union Window
	{
#ifndef RASPBERRY_COMPILE
		SDL_Window*			sdlWindow;
		sf::Window*         sfmlWindow;
		sf::RenderWindow*	sfml2DWindow;
#else
		EGLNativeWindowType eglWindow;
#endif // !RASPBERRY_COMPILE

	}window;
	ElEWindow() = delete;
	ElEWindow(const ElEGraphicsComponents& renderT);
	~ElEWindow();
private:
	ElEGraphicsComponents type;
};

class ElERender
{
public:
	union Render
	{
#ifndef RASPBERRY_COMPILE
		SDL_Renderer*		sdlRender;
		sf::RenderTexture*	sfmlRender;
#else
		EGLDisplay			eglRender;
#endif	//!RASPBERRY_COMPILE
	}render;
	ElERender() = delete;
	ElERender(const ElEGraphicsComponents& renderT);
	~ElERender();
private:
	ElEGraphicsComponents type;
};

class ElESurface
{
public:
	union Surface
	{
#ifndef RASPBERRY_COMPILE
		SDL_Surface*		sdlSurface;
		sf::Sprite*			sfmlSurface;
#else
		EGLSurface			eglSurface;
#endif	//!RASPBERRY_COMPILE
	}surface;
	ElESurface() = delete;
	ElESurface(const ElEGraphicsComponents& renderT);
	~ElESurface();
private:
	ElEGraphicsComponents type;
};

class ElETexture
{
public:
	union Texture
	{
#ifndef RASPBERRY_COMPILE
		SDL_Texture*		sdlTexture;
		sf::Texture*        sfmlTexture;
#else
		GLuint				eglTexture;
#endif	//!RASPBERRY_COMPILE
	}texture;
	ElETexture() = delete;
	ElETexture(const ElEGraphicsComponents& renderT);
	~ElETexture();
private:
	ElEGraphicsComponents type;
};

class ElEEvent {

};

class ElE
{
private:
	static ElEGraphicsComponents					graphicsComp;
	static ElEAudioComponents						audioComp;
	static ElEPhysicsComponents					physicsComp;
	static ElEint									setFlags;
	static ElEuint									screenWidth,
													screenHeight;
	static MotorFlags								motorFlags;
	static ElEWindow*								window;
	static ElERender*								render;
	static ElESurface*								surface;
	static ElETexture*								texture;
	static ElEGLContext*                           context;
	static std::vector<void(*)()>                initFunctions;
	static ElEchar*								windowTitle;
	static ElEThreadPool*							threadPool;
#ifndef RASPBERRY_COMPILE
	static SDL_Event								event;

#endif
public:
	static void ElEcall App(const _IN_ ElEGraphicsComponents&			graph,
					const _IN_ ElEAudioComponents&				audio,
					const _IN_ ElEPhysicsComponents&			phys,
					const _IN_ ElEint&							flags,
					const _IN_ MotorFlags&						mFlags,
					const _IN_ ElEuint&							width,
					const _IN_ ElEuint&							height,
					_IN_ ElEchar*								title);
	static inline ElEuint ElEcall getWidth() { return screenWidth; }
	static inline ElEuint ElEcall getHeight() { return screenHeight; }
	static inline ElERender* ElEcall getRender() { return render; }
	static inline ElESurface* ElEcall getSurface() { return surface; }
	static inline ElETexture* ElEcall getTexture() { return texture; }
	static inline ElEWindow* ElEcall getWindow() { return window; }
	static inline ElEGLContext* ElEcall getContext() { return context; }
 	static inline ElEGraphicsComponents ElEcall getGraphicsRenderer() { return graphicsComp; }
#ifdef RASPBERRY_COMPILE
	static void ElEcall PutPixel();

#endif
private:
	static void ElEcall PrepareJumpTables();
	static void ElEcall InitSFML();
	static void ElEcall InitSDL();
	static void ElEcall InitVulkan();
	static void ElEcall InitCDM();
	static void ElEcall InitOpenGLes20Rasp();
	static void ElEcall Init();
	static void ElEcall PollEvents();
#ifdef RASPBERRY_COMPILE
	static void ElEcall InitGLesPlane();
#endif
	ElE();
	~ElE();
};

