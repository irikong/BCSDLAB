#pragma once
#include "Collider.h"

class CColliderPoint :
	public CCollider
{
protected:
	friend class CObj;

	POSITION	m_tDist;
	POSITION	m_tPos;

	CColliderPoint();
	CColliderPoint(const CColliderPoint& coll);
	~CColliderPoint();

public:
	POSITION GetPoint() const { return m_tPos; }
	void SetDistance(const POSITION& tDist) { m_tDist = tDist; }
	void SetDistance(float x, float y)
	{
		m_tDist.x = x;
		m_tDist.y = y;
	}

	virtual bool			Init();
	virtual void			Input(float fDeltaTime);
	virtual int				Update(float fDeltaTime);
	virtual int				LateUpdate(float fDeltaTime);
	virtual bool			Collision(CCollider* pDest);
	virtual void			Render(HDC hDC, float fDeltaTime);
	virtual CColliderPoint*	Clone();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};