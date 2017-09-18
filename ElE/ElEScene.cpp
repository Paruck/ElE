#include "ElEScene.h"
#include "ElE.h"

ElEScene::ElEScene()
{
}


ElEScene::~ElEScene()
{
	this->SceneEnd();
}

void ElEScene::Start()
{
}

void ElEScene::Update()
{
}

void ElEScene::Draw()
{
    switch(ElE::getGraphicsRenderer())
    {
    #ifdef RASPBERRY_COMPILE
        case ElEGraphicsComponents::OpenGLes20Rasp:

            break;
    #endif // RASPBERRY_COMPILE
    }
}

void ElEScene::SceneEnd()
{
}
