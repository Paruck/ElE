#pragma once
#include <SDL\SDL.h>
#include <SFML\Main.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include "ElEDefines.h"

typedef enum ElEPhysicsComponents 
{
	Box2D,
}ElEPhysicsComponents;

typedef enum ElEGraphicsComponents 
{
	OpenGL,
	Vulkan,
	CDM,
}ElEGraphicsComponents;

typedef enum ElEAudioComponents 
{
	SFML,
	SDL,
}ElEAudioComponents;

typedef enum Flags 
{
	fullScreen		=	0x00000001,
	resizable		=	0x00000002,
	openGL			=	0x00000004,
	shown			=   0x00000008,
	hidden			=   0x00000010,
	borderless		=   0x00000020,
	resizable		=   0x00000040,
	minimized		=   0x00000080,
	maximized		=   0x00000100,
	inputGrabbed	=   0x00000200,
	inputFocus		=	0x00000400,
	mouseFocus		=	0x00000800,
	SDLforeign		=	0x00001000,
	highDPI			=	0x00002000,
	mouseCapture	=	0x00004000,
	alwaysOnTop		=	0x00008000,
	skipTaskBar		=	0x00010000,
	tooltip			=	0x00020000,
	popUpMenu		=	0x00040000,
	SDLTimer		=	0x00080000,
	SDLVideo		=	0x00100000,
	SDLJoystick		=	0x00200000,
	SDLHaptic		=	0x00400000,
	SDLGameCtrl		=	0x00800000,
	SDLEvents		=	0x01000000,
	SDLEverything	=	0x02000000,
	autoFlags		=	0x00000000,
}Flags;

class ElE
{
public:
	static void App(const _IN_ ElEGraphicsComponents&			graph,
					const _IN_ ElEAudioComponents&				audio,
					const _IN_ ElEPhysicsComponents&			phys,
					const _IN_ Flags&							flags,
					const _IN_ int&								width,
					const _IN_ int&								height);
private:
	static void Init(const _IN_ Flags& flags);
	ElE();
	~ElE();
};

