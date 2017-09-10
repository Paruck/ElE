#pragma once
#include "ElEDefines.h"
#ifdef RASPBERRY_COMPILE
#include "GLES2/gl2.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#endif
class ElEShader {
public:
	ElEShader() = delete;
	ElEShader(const ElEGraphicsComponents& renderT);
	~ElEShader();
	ElEvoid __cdecl LoadFragmentShader(const ElEchar* filename);
	ElEvoid __cdecl LoadVertexShader(const ElEchar* filename);
	inline ElEuint __cdecl getID() { return id; }
	inline ElEShaderTypes __cdecl getShaderType() { return shaderType; }
private:
	ElEchar*				src = nullptr;
	ElEuint					id = 0;
	ElEShaderTypes			shaderType;
	ElEGraphicsComponents	type;

};


