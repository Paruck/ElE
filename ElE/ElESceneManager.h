#pragma once
#include "ElEDefines.h"
#include "ElEScene.h"
#include "ElEThread.h"
#include "ElEQueue.h"
#include <mutex>
#include <functional>

class ElESceneManager
{
public:
	~ElESceneManager();
	inline static ElESceneManager* ElEcall getInstance()
	{
		return instance == nullptr ? instance = new ElESceneManager() : instance;
	}
	void ElEcall ChangeScene(_IN_ ElEScene* const& val);
	inline const ElEScene* getScene() { return scene; }
	void ElEcall SceneMainLoop();
private:
	static ElESceneManager*				instance;
	ElEbool								sceneIsChanging = ElEfalse;
	std::mutex							drawMutex;
	ElEScene*							scene = nullptr;
	ElESceneManager();
	void ElEcall Draw();
};

