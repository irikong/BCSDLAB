#pragma once
#include "Scene.h"
class CInGameScene :
	public CScene
{
private:
	friend class CSceneManager;

	CInGameScene();
	~CInGameScene();

public:
	virtual bool Init();
};