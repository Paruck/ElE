#pragma once
#include "ElEDefines.h"
class ElEShader {
public:
	ElEShader() = delete;
	ElEShader(const ElEGraphicsComponents& renderT);
	~ElEShader();
	void __cdecl LoadFragmentShader(const ElEchar* filename);
	void __cdecl LoadVertexShader(const ElEchar* filename);
	inline ElEuint __cdecl getID() { return id; }
	inline ElEShaderTypes __cdecl getShaderType() { return shaderType; }
private:
	ElEchar*				src = nullptr;
	ElEuint					id = 0;
	ElEShaderTypes			shaderType;
	ElEGraphicsComponents	type;

};


