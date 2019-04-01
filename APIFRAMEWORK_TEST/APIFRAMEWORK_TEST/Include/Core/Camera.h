#pragma once

#include "../Game.h"

class CCamera
{
private:
	POSITION		m_tPos;
	RESOLUTION		m_tClientRS;
	RESOLUTION		m_tWorldRS;
	POSITION		m_tPivot;

	class CObj*		m_pTarget;

public:
	void SetTarget(class CObj* pObj);

	void SetPivot(const POSITION& tPivot) { m_tPivot = tPivot; }
	void SetPivot(float x, float y) { m_tPivot = POSITION(x, y); }

	void SetPos(const POSITION& tPos) { m_tPos = tPos; }
	void SetPos(float x, float y) { m_tPos = POSITION(x, y); }

	void SetClientResolution(const RESOLUTION& tRS) { m_tClientRS = tRS; }
	void SetClientResolution(float x, float y) { m_tClientRS = RESOLUTION((int)x, (int)y); }

	void SetWorldResolution(const RESOLUTION& tRS) { m_tWorldRS = tRS; }
	void SetWorldResolution(float x, float y) { m_tWorldRS = RESOLUTION((int)x, (int)y); }

	POSITION GetPos() const { return m_tPos; }
	RESOLUTION GetCllientRS() const { return m_tClientRS; }

	bool Init(const POSITION& tPos, const RESOLUTION& tRS,
		const RESOLUTION& tWorldRS);
	void Input(float fDeltaTime);
	void Update(float fDeltaTime);

	DECLARE_SINGLE(CCamera)
};

