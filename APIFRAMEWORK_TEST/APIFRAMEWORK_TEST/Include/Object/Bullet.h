#pragma once
#include "MoveObj.h"
class CBullet :
	public CMoveObj
{
private:
	float	m_fLimitDist;
	float	m_fDist;

	friend class CObj;
	friend class CScene;

	CBullet();
	CBullet(const CBullet& bullet);
	~CBullet();

public:
	virtual bool	Init();
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual void	Collision(float fDeltaTime);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CBullet*	Clone();

	void SetBulletDistance(float fDist) { m_fLimitDist = fDist; }
	void Hit(class CCollider* pSrc, class CCollider* pDest, float fDeltaTime);
};