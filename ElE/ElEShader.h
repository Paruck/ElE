#pragma once
#include "ElEDefines.h"
#ifdef RASPBERRY_COMPILE
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#endif
class ElEShader {
public:
	ElEShader() = delete;
	ElEShader(const ElEGraphicsComponents& renderT);
	~ElEShader();
	ElEvoid ElEcall LoadFragmentShader(const ElEchar* filename);
	ElEvoid ElEcall LoadVertexShader(const ElEchar* filename);
	inline ElEuint ElEcall getID() { return id; }
	inline ElEShaderTypes ElEcall getShaderType() { return shaderType; }
private:
	ElEchar*				src = nullptr;
	ElEuint					id = 0;
	ElEShaderTypes			shaderType;
	ElEGraphicsComponents	type;

};


