#pragma once
#define _IN_
#define _OUT_
#define _IN_OUT_
//#define WIN32_COMPILE
//#define RASPBERRY_COMPILE



#ifdef RASPBERRY_COMPILE
#define ElEcall
#else
#define ElEcall __cdecl
#endif

typedef enum ElEBoolean
{
	ElEfalse = 0,
	ElEtrue,
}ElEBoolean;

#ifdef RASPBERRY_COMPILE
#include <inttypes.h>
#include <cstdint>
typedef int32_t			ElEint;
typedef uint32_t			ElEuint;
typedef int8_t				ElEbyte;
typedef uint8_t			ElEubyte;
typedef uint32_t			ElEsize_t;

#else
typedef __int32				ElEint;
typedef unsigned __int32	ElEuint;
typedef __int8				ElEbyte;
typedef unsigned __int8		ElEubyte;
typedef unsigned __int32	ElEsize_t;

#endif

typedef ElEBoolean			ElEbool;
typedef char				ElEchar;
typedef unsigned char		ElEuchar;
typedef void				ElEvoid;
typedef short				ElEshort;
typedef unsigned short	ElEushort;
typedef double				ElEdouble;
typedef ElEbool			FLAG;
typedef float				ElEfloat;

const ElEint	threadAmmount = 4;
const ElEfloat	PI = 3.1415f;
const ElEfloat	degtorad = PI / 180.f;

typedef struct ElEPosHelper
{
    ElEint x, y;
}ElEPosHelper;

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

typedef enum ElEKey{
    kb_A = 0,
    kb_B,
    kb_C,
    kb_D,
    kb_E,
    kb_F,
    kb_G,
    kb_H,
    kb_I,
    kb_J,
    kb_K,
    kb_L,
    kb_M,
    kb_N,
    kb_O,
    kb_P,
    kb_Q,
    kb_R,
    kb_S,
    kb_T,
    kb_U,
    kb_V,
    kb_W,
    kb_X,
    kb_Y,
    kb_Z,
    kb_return,
    kb_lshift,
    kb_rshift,
    kb_lctrl,
    kb_rctrl,
    kb_lalt,
    kb_ralt,
    kb_1,
    kb_2,
    kb_3,
    kb_4,
    kb_5,
    kb_6,
    kb_7,
    kb_8,
    kb_9,
    kb_0,
    kb_tab,
    kb_mayus,
    kb_esc,
    numpad_1,
    numpad_2,
    numpad_3,
    numpad_4,
    numpad_5,
    numpad_6,
    numpad_7,
    numpad_8,
    numpad_9,
    numpad_0,
    mb_left,
    mb_right,
    mb_middle
}ElEKey;

typedef union MotorFlags
{
	SDLFlags			sdl;
	SFMLFlags			sfml;
}MotorFlags;


