#pragma once
#include "Obj.h"
class CMoveObj :
	public CObj
{
protected:
	CMoveObj();
	CMoveObj(const CMoveObj& obj);
	virtual ~CMoveObj();

	float		m_fAngle;
	float		m_fSpeed;
	float		m_fForce;
	float		m_fForceOrigin;
	bool		m_bMove;
	bool		m_bFalling;

public:
	float GetAngle() const { return m_fAngle; }
	void SetAngle(float fAngle) { m_fAngle = fAngle; }

	float GetSpeed() const { return m_fSpeed; }
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

	void SetForce(float fForce) { m_fForceOrigin = fForce; }

	void Move(float x, float y);
	void Move(float x, float y, float fDeltaTime);
	void Move(const POSITION& tMove);
	void Move(const POSITION& tMove, float fDeltaTime);
	void MoveX(float x);
	void MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir);
	void MoveX(float x, float fDeltaTime);
	void MoveY(float y);
	void MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir);
	void MoveY(float y, float fDeltaTime);
	void MoveAngle();
	void MoveAngle(float fDeltaTime);

	void Jump();
	void JumpEnd();

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int	Update(float fDeltaTime);
	virtual int	LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMoveObj* Clone() = 0;
};

