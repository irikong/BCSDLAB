#pragma once

#include "..\Game.h"

class CLayer
{
private:
	friend class CScene;
	CLayer();

	list<class CObj*> m_ObjList;
	class CScene* m_pScene;
	
	string		m_strTag;
	int			m_iZOrder; // �������� ���̾���� ��� �켱 ������ �����ݴϴ�.
	bool		m_bEnable;
	bool		m_bLife;

public:
	~CLayer();

	void SetEnable(bool bEnable) { m_bEnable = bEnable; }

	void Die() { m_bLife = false; }

	bool GetEnable() const { return m_bEnable; }

	bool GetLife() const { return m_bLife; }

	void SetTag(const string& strTag) {	m_strTag = strTag; }

	void SetZOrder(int iZOrder) { m_iZOrder = iZOrder; }

	void SetScene(CScene* pScene) {	m_pScene = pScene; }

	int GetZOrder() const { return m_iZOrder; }

	string GetTag() const { return m_strTag; }

	CScene* GetScene() const { return m_pScene; }

	void AddObject(CObj* pObj);
	void Input(float fDeltaTime);
	int	Update(float fDeltaTime);
	int	LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
};