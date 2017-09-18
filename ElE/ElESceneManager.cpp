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
		if (scene && !sceneIsChanging)
			scene->Draw();
	}
}


ElESceneManager::~ElESceneManager()
{
}

void ElESceneManager::ChangeScene(_IN_ ElEScene * const & val)
{
	sceneIsChanging = ElEtrue;
	if (scene)
		delete scene;
	scene = val;
	if (scene)
	{
		scene->Start();
	}
	sceneIsChanging = ElEfalse;
}

void ElESceneManager::SceneMainLoop()
{
	using namespace std;
	using namespace chrono;
	if(scene)
		scene->Update();
	//this_thread::sleep_for(16ms);
}
