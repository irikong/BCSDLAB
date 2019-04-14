#pragma once
#include "Scene.h"
class CStartScene :
	public CScene
{
private:
	friend class CSceneManager;

	CStartScene();
	~CStartScene();

public:
	virtual bool Init();

	void StartButtonCallback(float fTime);
	void EndButtonCallback(float fTime);
};