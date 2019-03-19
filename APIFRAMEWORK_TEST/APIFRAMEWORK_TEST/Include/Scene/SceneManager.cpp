#include "SceneManager.h"
#include "InGameScene.h"

DEFINITION_SINGLE(SceneManager)

SceneManager::SceneManager() :
	m_pScene(NULL),
	m_pNextScene(NULL)
{
}


SceneManager::~SceneManager()
{
	SAFE_DELETE(m_pScene);
}
	
bool SceneManager::Init()
{
	CreateScene<InGameScene>(SC_CURRENT);
	
	return true;
}
