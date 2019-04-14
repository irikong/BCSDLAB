#pragma once
#include "Scene.h"

class CMapEditScene :
	public CScene
{
private:
	friend class CSceneManager;

	CMapEditScene();
	~CMapEditScene();

public:
	virtual bool Init();
};

