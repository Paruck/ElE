#pragma once
class ElEScene
{
public:
	ElEScene();
	~ElEScene();
	virtual void __cdecl Start();
	virtual void __cdecl Update();
	virtual void __cdecl Draw();
	virtual void __cdecl SceneEnd();
};

