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
	inline static ElESceneManager* __cdecl getInstance()
	{
		return instance == nullptr ? instance = new ElESceneManager() : instance;
	}
	void __cdecl ChangeScene(_IN_ ElEScene* const& val);
	inline const ElEScene* getScene() { return scene; }
	void __cdecl SceneMainLoop();
private:
	static ElESceneManager*				instance;
	ElEbool								cleanupRequested = ElEfalse;
	std::mutex							drawMutex;
	ElEQueue<std::function<void()>>		drawQueue;
	ElEScene*							scene = nullptr;
	ElESceneManager();
	void __cdecl Draw();
};

