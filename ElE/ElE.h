#pragma once
#include <SDL\SDL.h>
#include <SFML\Main.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML/Graphics.hpp>
#include <SDL\SDL_ttf.h>
#include <SDL\SDL_mixer.h>
#include <SDL\SDL_image.h>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <iostream>
#include "ElEDefines.h"

typedef enum ElEPhysicsComponents 
{
	Box2D,
	PhysX,
}ElEPhysicsComponents;

typedef enum ElEGraphicsComponents 
{
	OpenGL,
	SDLGraphics,
	Vulkan,
	CDM,
}ElEGraphicsComponents;

typedef enum ElEAudioComponents 
{
	SFML,
	SDLAudio,
}ElEAudioComponents;

typedef enum SDLFlags 
{
	SDLTimer		=	0x00080000,
	SDLVideo		=	0x00100000,
	SDLJoystick		=	0x00200000,
	SDLHaptic		=	0x00400000,
	SDLGameCtrl		=	0x00800000,
	SDLEvents		=	0x01000000,
	SDLEverything	=	0x02000000,
	autoFlagsSDL	=	0x00000000,
}SDLFlags;

typedef enum SFMLFlags 
{
	SFMLTimer		=	0x00000100,

}SFMLFlags;

typedef enum WindowFlags
{
	fullScreen		= 0x00000001,
	resizable		= 0x00000002,
	openGL			= 0x00000004,
	shown			= 0x00000008,
	hidden			= 0x00000010,
	borderless		= 0x00000020,
	minimized		= 0x00000080,
	maximized		= 0x00000100,
	inputGrabbed	= 0x00000200,
	inputFocus		= 0x00000400,
	mouseFocus		= 0x00000800,
	SDLforeign		= 0x00001000,
	highDPI			= 0x00002000,
	mouseCapture	= 0x00004000,
	alwaysOnTop		= 0x00008000,
	skipTaskBar		= 0x00010000,
	tooltip			= 0x00020000,
	popUpMenu		= 0x00040000,
	autoFlagsW		= 0x00000000,
}WindowFlags;

typedef union MotorFlags
{
	SDLFlags			sdl;
	SFMLFlags			sfml;
}MotorFlags;

typedef union ElEWindow 
{
	SDL_Window*			sdlWindow;
	sf::Window*         sfmlWindow;
	sf::RenderWindow*	sfml2DWindow;

}ElEWindow;

typedef union ElERender
{
	SDL_Renderer*		sdlRender;
	sf::RenderTexture	sfmlRender;

}ElERender;

typedef union ElESurface
{
	SDL_Surface*		sdlSurface;
	sf::Sprite*			sfmlSurface;
}ElESurface;

typedef union ElETexture
{
	SDL_Texture*		sdlTexture;
	sf::Texture*        sfmlTexture;

}ElETexture;

class ElE
{
private:
	static ElEGraphicsComponents					graphicsComp;
	static ElEAudioComponents						audioComp;
	static ElEPhysicsComponents						physicsComp;
	static WindowFlags								setFlags;
	static MotorFlags								motorFlags;
	static ElEWindow								window;
	static ElERender								render;
	static ElESurface								surface;
	static ElETexture								texture;
	static std::vector<std::function<void()>>		initFunctions;
	static int										screenWidth,
													screenHeight;
public:
	static void App(const _IN_ ElEGraphicsComponents&			graph,
					const _IN_ ElEAudioComponents&				audio,
					const _IN_ ElEPhysicsComponents&			phys,
					const _IN_ WindowFlags&						flags,
					const _IN_ MotorFlags&						mFlags,
					const _IN_ int&								width,
					const _IN_ int&								height);
private:
	static void PrepareJumpTables();
	static void InitSFML();
	static void InitSDL();
	static void InitVulkan();
	static void InitCDM();
	static void Init();
	ElE();
	~ElE();
};

