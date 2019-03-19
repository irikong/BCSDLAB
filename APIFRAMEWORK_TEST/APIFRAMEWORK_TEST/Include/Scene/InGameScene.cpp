#include "InGameScene.h"



InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

bool InGameScene::Init()
{
	// 부모 Scene 클래스의 초기화 함수를 호출해준다.
	if (!Scene::Init()) return false;
	return true;
}
