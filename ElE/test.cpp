#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "bcm_host.h"
#include <errno.h>
#include <regex.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <vector>
//#include "glm/glm.hpp"


#define GLSUCCESS 0


typedef enum ElEBoolean
{
	ElEfalse = 0,
	ElEtrue,
}ElEBoolean;
#include <inttypes.h>
#include <cstdint>
typedef int32_t			ElEint;
typedef uint32_t		ElEuint;
typedef int8_t			ElEbyte;
typedef uint8_t			ElEubyte;
typedef uint32_t		ElEsize_t;

typedef ElEBoolean		ElEbool;
typedef char			ElEchar;
typedef unsigned char		ElEuchar;
typedef void			ElEvoid;
typedef short			ElEshort;
typedef unsigned short		ElEushort;
typedef double			ElEdouble;
typedef ElEbool			FLAG;
typedef float			ElEfloat;

typedef std::vector<ElEfloat>	ElEVertex;
typedef std::vector<ElEubyte>	ElEIndexes;

ElEint  kbfd = -1,
        mfd = -1;

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

ElEbool keyPressed(const ElEKey& key)
{

    if(kbfd == -1)
    {
        DIR             *dirp = nullptr;
        struct dirent  *dp = nullptr;
        regex_t         kbd,
                        mouse;
        ElEchar         fullPath[1024];
        static ElEchar  *dirName = "/dev/input/by-id";
        ElEint          result;
        if(regcomp(&kbd, "event-kbd", 0) != 0)
        {
            printf("regcomp for kbd failed\n");
            return ElEfalse;
        }
        if(regcomp(&mouse, "event-mouse", 0) != 0)
        {
            printf("regcomp for kbd failed\n");
            return ElEfalse;
        }
        if((dirp = opendir(dirName)) == nullptr)
        {
            perror("couldn't open '/dev/input/by-id'");
            return ElEfalse;
        }
        do
        {
            errno = 0;
            if((dp = readdir(dirp)) != nullptr)
            {
                if(regexec (&kbd, dp->d_name, 0, NULL, 0) == 0)
                {
                    sprintf(fullPath,"%s/%s",dirName,dp->d_name);
                    kbfd = open(fullPath, O_RDONLY | O_NONBLOCK);
                    result  = ioctl(kbfd, EVIOCGRAB, 1);
                }
                if(regexec (&mouse, dp->d_name, 0, NULL, 0) == 0)
                {
                    sprintf(fullPath,"%s/%s",dirName,dp->d_name);
                    mfd = open(fullPath, O_RDONLY | O_NONBLOCK);
                    result  = ioctl(mfd, EVIOCGRAB, 1);
                }
            }
        }while (dp != nullptr);
        closedir(dirp);
        regfree(&kbd);
        regfree(&mouse);
    }
    struct input_event ev[64];
    ElEint rd = read(mfd,ev,sizeof(ev));
    if(rd > 0)
    {
        ElEint              count,
                            n;
        struct input_event *evp;
        count  = rd / sizeof(struct input_event);
        n = 0;
        while(count--)
        {
            evp = &ev[n++];
            if(evp->code == BTN_LEFT && key == mb_left)
            {
                if(evp->type == 1)
                {
                    if(evp->value == 1)
                        return ElEtrue;
                    else
                        return ElEfalse;
                }
            }
            else if(evp->code == BTN_RIGHT && key == mb_right)
            {
                if(evp->type == 1)
                {
                    if(evp->value == 1)
                        return ElEtrue;
                    else
                        return ElEfalse;
                }
            }
            else if(evp->code == BTN_MIDDLE && key == mb_middle)
            {
                if(evp->type == 1)
                {
                    if(evp->value == 1)
                        return ElEtrue;
                    else
                        return ElEfalse;
                }
            }
        }
    }

    rd = read(kbfd, ev, sizeof(ev));
    if(rd > 0)
    {
        ElEint              count,
                            n;
        struct input_event *evp;
        count  = rd / sizeof(struct input_event);
        n = 0;
        while(count--)
        {
            evp = &ev[n++];
            if(evp->type == 1)
            {
                if(evp->value == 1)
                {
                    if(evp->code == KEY_A && key == kb_A)
                        return ElEtrue;
                    else if(evp->code == KEY_B && key == kb_B)
                        return ElEtrue;
                    else if(evp->code == KEY_C && key == kb_C)
                        return ElEtrue;
                    else if(evp->code == KEY_D && key == kb_D)
                        return ElEtrue;
                    else if(evp->code == KEY_E && key == kb_E)
                        return ElEtrue;
                    else if(evp->code == KEY_F && key == kb_F)
                        return ElEtrue;
                    else if(evp->code == KEY_G && key == kb_G)
                        return ElEtrue;
                    else if(evp->code == KEY_H && key == kb_H)
                        return ElEtrue;
                    else if(evp->code == KEY_I && key == kb_I)
                        return ElEtrue;
                    else if(evp->code == KEY_J && key == kb_J)
                        return ElEtrue;
                    else if(evp->code == KEY_K && key == kb_K)
                        return ElEtrue;
                    else if(evp->code == KEY_L && key == kb_L)
                        return ElEtrue;
                    else if(evp->code == KEY_M && key == kb_M)
                        return ElEtrue;
                    else if(evp->code == KEY_N && key == kb_N)
                        return ElEtrue;
                    else if(evp->code == KEY_O && key == kb_O)
                        return ElEtrue;
                    else if(evp->code == KEY_P && key == kb_P)
                        return ElEtrue;
                    else if(evp->code == KEY_Q && key == kb_Q)
                        return ElEtrue;
                    else if(evp->code == KEY_R && key == kb_R)
                        return ElEtrue;
                    else if(evp->code == KEY_S && key == kb_S)
                        return ElEtrue;
                    else if(evp->code == KEY_T && key == kb_T)
                        return ElEtrue;
                    else if(evp->code == KEY_U && key == kb_U)
                        return ElEtrue;
                    else if(evp->code == KEY_W && key == kb_W)
                        return ElEtrue;
                    else if(evp->code == KEY_X && key == kb_X)
                        return ElEtrue;
                    else if(evp->code == KEY_Y && key == kb_Y)
                        return ElEtrue;
                    else if(evp->code == KEY_Z && key == kb_Z)
                        return ElEtrue;
                    else if(evp->code == KEY_ESC && key == kb_esc)
                        return ElEtrue;
                    else if(evp->code == KEY_LEFTALT && key == kb_lalt)
                        return ElEtrue;
                    else if(evp->code == KEY_RIGHTALT && key == kb_ralt)
                        return ElEtrue;
                    else if(evp->code == KEY_LEFTSHIFT && key == kb_lshift)
                        return ElEtrue;
                    else if(evp->code == KEY_RIGHTSHIFT && key == kb_rshift)
                        return ElEtrue;
                    else if(evp->code == KEY_LEFTCTRL && key == kb_lctrl)
                        return ElEtrue;
                    else if(evp->code == KEY_RIGHTCTRL && key == kb_rctrl)
                        return ElEtrue;
                    else if(evp->code == KEY_ENTER && key == kb_return)
                        return ElEtrue;
                }
            }
        }
    }
    return ElEfalse;
}






GLuint			screenWidth 	= 720,
			screenHeight 	= 576;
EGLDisplay		display;
EGLSurface		surface;
EGLContext		context;
EGLBoolean		result;
EGLNativeWindowType	hWnd;

typedef struct
{
	GLuint programObject;
} UserData;

GLuint LoadShader(const char *shaderSrc, GLenum type)
{
	GLuint shader;
	GLint compiled;

	shader = glCreateShader(type);

	if(shader == 0)
		return 0;
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
 	if(!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Error compiling shader:\n%s\n", infoLog);
			free(infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}
/*
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/trigonometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

glm::mat4 transform( glm::vec2 const& Orientation, glm::vec3 const& Translate,
        glm::vec3 const& Up)
{
        glm::mat4 Proj = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
        glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f),Translate);
        glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
        glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
        glm::mat4 Model = glm::mat4(1.0f);
        return Proj * View * Model;
}
*/

int Init(GLuint &programid)
{
 	const GLbyte vShaderStr[] =
 		"attribute vec4 vPosition; 	\n"
		"void main()			\n"
 		"{ 				\n"
 		" gl_Position = vPosition;\n"
 		"} 			   	\n";

 	const GLbyte fShaderStr[] =
		 "precision mediump float; 			\n"
		 "void main() 					\n"
 		"{ 						\n"
 		" gl_FragColor = vec4(0.5, 0.5, 0.4, 1.0); 	\n"
 		"} 						\n";
 	GLuint vertexShader;
 	GLuint fragmentShader;
 	GLuint programObject;
 	GLint linked;
	 // Load the vertex/fragment shaders
 	vertexShader = LoadShader((const char*)vShaderStr, GL_VERTEX_SHADER);
 	fragmentShader = LoadShader((const char*)fShaderStr, GL_FRAGMENT_SHADER);
	// Create the program object
 	programObject = glCreateProgram();
	if(programObject == 0)
 		return 0;
 	glAttachShader(programObject, vertexShader);
 	glAttachShader(programObject, fragmentShader);
 	// Bind vPosition to attribute 0
 	glBindAttribLocation(programObject, 0, "vPosition");
	//glm::mat4 mvp = transform(glm::vec2(0.0f), glm::vec3(-1.0f, -1.0f, -100.0f), glm::vec3(0.0f,1.0f,0.0f)); 
	//int mvpIndex = glGetUniformLocation(programObject, "mvp");
	//glUniformMatrix4fv(mvpIndex, 1, GL_FALSE, glm::value_ptr(mvp));
 	// Link the program
 	glLinkProgram(programObject);
 	// Check the link status
 	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
 	if(!linked)
 	{
 		GLint infoLen = 0;
 		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1)
 		{
 			char* infoLog = (char*)malloc(sizeof(char) * infoLen);
 			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
 			printf("Error linking program:\n%s\n", infoLog);
 	 		free(infoLog);
 		}
 		glDeleteProgram(programObject);
 		return 0;
 	}
 	// Store the program object
 	programid = programObject;
 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 	return 1;
}
ElEIndexes index1;
ElEVertex verts1;

void Start()
{

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); // 1
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); // 2
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); // 3

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); // 4
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); // 5
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); // 6
//////////////////////////////////////////1

    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);

    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
////////////////////////////////////////////////////////////2

    verts1.push_back(0); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);

    verts1.push_back(1); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    //////////////////////////////////////////////////////////////3

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(0); verts1.push_back(0); verts1.push_back(1);
    ////////////////////////////////////////4

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);

    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(0); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    /////////////////////////////////5

    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(0); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);

    verts1.push_back(0); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(1); verts1.push_back(1); verts1.push_back(1);
    verts1.push_back(1); verts1.push_back(0); verts1.push_back(1); verts1.push_back(1);
    for(ElEint i = 0; i < verts1.size(); ++i)
    	index1.push_back(i);
}


void Draw(GLint programid, GLuint width, GLuint height, EGLDisplay &disp)
{
    	if(keyPressed(kb_esc))
        	exit(0);
	if(keyPressed(kb_W))
	{
		printf("PRESIONE W");
		for(int i = 0; i < verts1.size(); ++i)
		{
			if(i%4 == 1)
				verts1.at(i) += .1f;
		}
	}
        if(keyPressed(kb_S))
        { 
                for(int i = 0; i < verts1.size(); ++i)
                {
                        if(i%4 == 1)
                                verts1.at(i) -= .1f;
                }
        }
        if(keyPressed(kb_A))
        { 
                for(int i = 0; i < verts1.size(); ++i)
                {
                        if(i%4 == 0)
                                verts1.at(i) -= .1f;
                }
        }
        if(keyPressed(kb_D))
        { 
                for(int i = 0; i < verts1.size(); ++i)
                {
                        if(i%4 == 0)
                                verts1.at(i) += .1f;
                }
        }

 	// Set the viewport
 	glViewport(0, 0, width, height);

 	// Clear the color buffer
 	glClear(GL_COLOR_BUFFER_BIT);
 	// Use the program object
 	glUseProgram(programid);
 	// Load the vertex data
 	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, &verts1.front());
 	glEnableVertexAttribArray(0);
 	glDrawElements(GL_TRIANGLES,  verts1.size()/4, GL_UNSIGNED_BYTE, &index1.front());
 	eglSwapBuffers(disp, surface);
}

int main()
{
	bcm_host_init();
	EGLint				success = 0;
	EGLint 				num_config;
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

	dst_rect.x 	= 0;
	dst_rect.y 	= 0;
	dst_rect.width 	= screenWidth;
	dst_rect.height = screenHeight;

	src_rect.x 	= 0;
	src_rect.y 	= 0;
	src_rect.width 	= screenWidth << 16;
	src_rect.height = screenHeight << 16;

	dispman_display = vc_dispmanx_display_open(0);
	dispman_update 	= vc_dispmanx_update_start(0);

	dispman_element = vc_dispmanx_element_add (
		dispman_update, dispman_display, 0,
		&dst_rect, 0, &src_rect,
		DISPMANX_PROTECTION_NONE, 0, 0,
		(DISPMANX_TRANSFORM_T)0);

	nativeWindow.element 	= dispman_element;
	nativeWindow.width 	= screenWidth;
	nativeWindow.height	= screenHeight;
	vc_dispmanx_update_submit_sync(dispman_update);

	hWnd = &nativeWindow;
	surface = eglCreateWindowSurface(display, config,
			 hWnd, NULL);
	assert(surface != EGL_NO_SURFACE);

	result = eglMakeCurrent(display, surface, surface, context);
	assert(result != EGL_FALSE);

	glClearColor(0.5f,0.7f,0.7f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, screenWidth, screenHeight);
	eglSwapBuffers(display,surface);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_SCISSOR_TEST);
	std::cout<<"HOLI"<<std::endl;
	GLuint programid;

	if(!Init(programid))
		return 0;
	Start();
	while(1)
	{
		Draw(programid, screenWidth, screenHeight, display);
	}
	return 0;
}
