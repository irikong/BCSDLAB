#pragma once

#include "..\Game.h"

class CLayer
{
private:
	friend class CScene;

private:
	CLayer();

public:
	~CLayer();

private:
	class CScene* m_pScene;
	string m_strTag;
	int m_iZOrder; // 여러가지 레이어들의 출력 우선 순위를 정해줍니다.
	list<class CObj*> m_ObjList;
	bool m_bEnable;
	bool m_bLife;

public:
	void SetEnable(bool bEnable) { m_bEnable = bEnable; }

	void Die() { m_bLife = false; }

	bool GetEnable() const { return m_bEnable; }

	bool GetLife() const { return m_bLife; }

public:
	void SetTag(const string& strTag) {	m_strTag = strTag; }

	void SetZOrder(int iZOrder) { m_iZOrder = iZOrder; }

	void SetScene(CScene* pScene) {	m_pScene = pScene; }

	int GetZOrder() const { return m_iZOrder; }

	string GetTag() const { return m_strTag; }

	CScene* GetScene() const { return m_pScene; }

public:
	void AddObject(CObj* pObj);
	void Input(float fDeltaTime);
	int	Update(float fDeltaTime);
	int	LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
};