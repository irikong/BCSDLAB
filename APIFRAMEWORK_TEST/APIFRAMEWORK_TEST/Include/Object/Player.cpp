#include "Player.h"
#include "..\Core\Input.h"
#include "Bullet.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer & player) :
	CMoveObj(player)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Fire()
{
	//m_bAttack = true;

	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);
	
	pBullet->AddCollisionFunction("BulletBody", CS_STAY, (CBullet*)pBullet, &CBullet::Hit);

	// 오른쪽 가운데를 구한다.
	POSITION tPos;
	//pBullet->SetPos(m_tPos.x + m_tSize.x, (m_tPos.y + m_tPos.y + m_tSize.y) / 2.f - pBullet->GetSize().y / 2.f);
	//if (m_iDir == -1)
		//tPos.x = GetLeft() - pBullet->GetSize().x * (1.f - pBullet->GetPivot().x);

	//else
		//tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = GetCenter().y;

	pBullet->SetPos(tPos);

	//if (m_iDir == -1)
		//((CMoveObj*)pBullet)->SetAngle(PI);

	SAFE_RELEASE(pBullet);
}

bool CPlayer::Init()
{
	SetPos(50.f, 50.f);
	SetSize(100.f, 100.f);
	// SetSize(256.f, 256.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Player", L"HOS.bmp");
	SetColorKey(255, 255, 255);

	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");

	pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
	// pRC->SetRect(-128.f, -128.f, 128.f, 128.f);
	pRC->AddCollisionFunction(CS_ENTER, this, &CPlayer::Hit);
	pRC->AddCollisionFunction(CS_STAY, this, &CPlayer::HitStay);

	SAFE_RELEASE(pRC);

	m_iHP = 1000;

	SetPhysics(true); // 중력 적용

	SetForce(300.f); // 점프할 힘을 설정한다.

	CAnimation* pAni = CreateAnimation("PlayerAnimation");

	AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOOP, 0.3f, 3, 1,
		0, 0, 3, 1, 0.f, "PlayerIdleLeft",
		L"Player/Idle/Left/Player_Idle_Left.bmp");
	SetAnimationClipColorKey("IdleLeft", 255, 255, 255);
	
	AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP, 0.3f, 3, 1,
		0, 0, 3, 1, 0.f, "PlayerIdleRight",
		L"Player/Idle/Right/Player_Idle_Right.bmp");
	SetAnimationClipColorKey("IdleRight", 255, 255, 255);

	SAFE_RELEASE(pAni);

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CMoveObj::Input(fDeltaTime);

	if (KEYDOWN("MoveFront")) // GetAsyncKeyState('W') & 0x8000
	{
		Jump();
		//MoveYFromSpeed(fDeltaTime, MD_BACK);
	}

	if (KEYDOWN("MoveBack")) // GetAsyncKeyState('S') & 0x8000
	{
		//MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (KEYPRESS("MoveLeft")) // GetAsyncKeyState('A') & 0x8000
	{
		MoveXFromSpeed(fDeltaTime, MD_BACK);
	}

	if (KEYPRESS("MoveRight")) // GetAsyncKeyState('D') & 0x8000
	{
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (KEYDOWN("Fire")) // GetAsyncKeyState(VK_SPACE) & 0x8000
	{
		Fire();
	}

	if (KEYDOWN("Skill1"))
	{
		MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);
	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
	wchar_t strHP[32] = {};
	wsprintf(strHP, L"HP : %d", m_iHP);
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();
	TextOut(hDC, (int)tPos.x, (int)tPos.y, strHP, lstrlen(strHP));
	//Rectangle(hDC, (int)m_tPos.x, (int)m_tPos.y, (int)(m_tPos.x + m_tSize.x), (int)(m_tPos.y + m_tSize.y));
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetObj()->GetTag() == "MinionBullet") {
		m_iHP -= 100;
	}

	else if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
	}
}

void CPlayer::HitStay(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "StageColl")
	{
		ClearGravity();
		JumpEnd();
		m_tPos.y = pSrc->GetHitPoint().y - m_tPivot.y * m_tSize.y;
	}
}