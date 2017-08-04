#pragma once
#include "ElEScene.h"
class ElEMainScene : public ElEScene
{
public:
	ElEMainScene();
	~ElEMainScene();
	void __cdecl Start() final;
	void __cdecl Update() final;
	void __cdecl Draw() final;
	void __cdecl SceneEnd() final;
};

