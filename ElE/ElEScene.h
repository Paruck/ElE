#pragma once
#include "ElEDefines.h"

class ElEScene
{
public:
	ElEScene();
	~ElEScene();
	virtual void ElEcall Start();
	virtual void ElEcall Update();
	virtual void ElEcall Draw();
	virtual void ElEcall SceneEnd();
};

