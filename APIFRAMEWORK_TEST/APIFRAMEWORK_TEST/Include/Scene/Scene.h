#pragma once

#include "..\Game.h"

class CScene
{
protected:
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0; // 자식의 소멸자가 실행되지 않는 것을 막기 위해 virtual 사용

protected:
	list<class CLayer*> m_LayerList;

public:
	class CLayer* CreateLayer(const string& strTag, int iZOrder = 0);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
};