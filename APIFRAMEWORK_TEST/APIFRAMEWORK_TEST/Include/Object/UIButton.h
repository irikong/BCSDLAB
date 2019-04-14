#pragma once
#include "UI.h"

enum BUTTON_STATE
{
	BS_NONE,
	BS_MOUSEON,
	BS_CLICK
};

class CUIButton :
	public CUI
{
private:
	friend class CObj;
	friend class CScene;

	CUIButton();
	CUIButton(const CUIButton& ui);
	~CUIButton();

	function<void(float fTime)> m_BtnCallback;
	BUTTON_STATE	m_eState;
	bool			m_bEnableCallback;

public:
	template <typename T>
	void SetCallback(T* pObj, void (T::*pFunc)(float))
	{
		m_BtnCallback = bind(pFunc, pObj, placeholders::_1);
		m_bEnableCallback = true;
	}

	void SetCallback(void(*pFunc)(float))
	{
		m_BtnCallback = bind(pFunc, placeholders::_1);
		m_bEnableCallback = true;
	}

	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual void	Collision(float fDeltaTime);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CUIButton*	Clone();

	void MouseOn(class CCollider* pSrc, class CCollider* pDest, float fDeltaTime);
	void MouseOut(class CCollider* pSrc, class CCollider* pDest, float fDeltaTime);
};