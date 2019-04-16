#pragma once
#include "Collider.h"
class CColliderSphere :
	public CCollider
{
private:
	SPHERE	m_tInfo;
	SPHERE	m_tWorldInfo;

protected:
	friend class CObj;

	CColliderSphere();
	CColliderSphere(const CColliderSphere& coll);
	~CColliderSphere();

public:
	void SetSphere(const POSITION& tCenter, float fRadius) {
		m_tInfo.tCenter = tCenter;
		m_tInfo.fRadius = fRadius;
	}
	SPHERE GetInfo() const { return m_tInfo; }
	SPHERE GetWorldInfo() const { return m_tWorldInfo; }

	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual bool	Collision(CCollider* pDest);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CColliderSphere*	Clone();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};