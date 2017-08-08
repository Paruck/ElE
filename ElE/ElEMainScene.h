#pragma once
#include "ElEScene.h"
#include "ElEDefines.h"
#include "ElEShader.h"
class ElEMainScene : public ElEScene
{
public:
	ElEMainScene();
	~ElEMainScene();
	void __cdecl Start() final;
	void __cdecl Update() final;
	void __cdecl Draw() final;
	void __cdecl SceneEnd() final;
private:
	ElEShader	*vertexS,
				*fragmentS;
	ElEuint		programID,
				*buffers;
};

