#include "ElESceneManager.h"
#include <chrono>


ElESceneManager* ElESceneManager::instance = nullptr;

ElESceneManager::ElESceneManager()
{
	ElEThreadPool::getInstance()->RequestThread(
		std::bind(&ElESceneManager::Draw, this))->DetachThread();
}

void ElESceneManager::Draw()
{
	using namespace std;
	using namespace chrono;
	while (1) {
		if (cleanupRequested)
		{
			drawMutex.lock();
			drawQueue.Clear();
			drawMutex.unlock();
			continue;
		}
		if (drawQueue.Empty())
		{
			this_thread::sleep_for(10ms);
			cleanupRequested = ElEfalse;
			continue;
		}
		drawMutex.lock();
		function<void()> f = drawQueue.Pop();
		drawMutex.unlock();
		f();
	}
}


ElESceneManager::~ElESceneManager()
{
}

void ElESceneManager::ChangeScene(_IN_ ElEScene * const & val)
{
	cleanupRequested = ElEtrue;
	while (cleanupRequested);
	if (scene)
		delete scene;
	scene = val;
	if (scene)
	{
		scene->Start();
	}
} 

void ElESceneManager::SceneMainLoop()
{
	using namespace std;
	using namespace chrono;
	if(scene)
		scene->Update();
	if(scene)
		//drawQueue.Add(std::bind(&ElEScene::Draw,&scene));
	this_thread::sleep_for(16ms);
}
