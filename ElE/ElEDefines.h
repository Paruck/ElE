#pragma once
#define _IN_
#define _OUT_
#define _IN_OUT_
#define WIN32_COMPILE
//#define RASPBERRY_COMPILE
typedef enum ElEBoolean
{
	ElEfalse = 0,
	ElEtrue,
}ElEBoolean;

typedef ElEBoolean			ElEbool;
typedef __int32				ElEint;
typedef unsigned __int32	ElEuint;
typedef char				ElEchar;
typedef unsigned char		ElEuchar;
typedef ElEbool				FLAG;

typedef struct ElERect {
	ElEint x, y;
	ElEint w, h;
}ElERect;

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
	OpenGLes20Rasp,
	CDM,
}ElEGraphicsComponents;

typedef enum ElEAudioComponents
{
	SFML,
	SDLAudio,
}ElEAudioComponents;

typedef enum SDLFlags
{
	SDLTimer = 0x00080000,
	SDLVideo = 0x00100000,
	SDLJoystick = 0x00200000,
	SDLHaptic = 0x00400000,
	SDLGameCtrl = 0x00800000,
	SDLEvents = 0x01000000,
	SDLEverything = 0x02000000,
	autoFlagsSDL = 0x00000000,
}SDLFlags;

typedef enum SFMLFlags
{
	SFMLTimer = 0x00000100,

}SFMLFlags;

typedef enum WindowFlags
{
	fullScreen = 0x00000001,
	resizable = 0x00000002,
	openGL = 0x00000004,
	shown = 0x00000008,
	hidden = 0x00000010,
	borderless = 0x00000020,
	minimized = 0x00000080,
	maximized = 0x00000100,
	inputGrabbed = 0x00000200,
	inputFocus = 0x00000400,
	mouseFocus = 0x00000800,
	SDLforeign = 0x00001000,
	highDPI = 0x00002000,
	mouseCapture = 0x00004000,
	alwaysOnTop = 0x00008000,
	skipTaskBar = 0x00010000,
	tooltip = 0x00020000,
	popUpMenu = 0x00040000,
	none = 0x00080000,
	titleBar = 0x00100000,
	closeButton = 0x00200000,
	autoFlagsW = 0x00000000,
}WindowFlags;

typedef enum ElEShaderTypes {
	pixelShader = 0,
	vertexShader,
	geometryShader,
	tesselationShader,
	primitiveShader,
	computeShader,
	fragmentShader
}ElEShaderTypes;

typedef union MotorFlags
{
	SDLFlags			sdl;
	SFMLFlags			sfml;
}MotorFlags;


