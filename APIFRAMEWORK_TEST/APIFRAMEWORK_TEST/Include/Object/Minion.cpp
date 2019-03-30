#include "Minion.h"
#include "..\Core.h"


CMinion::CMinion() :
	m_fFireTime(0.f),
	m_fFireLimitTime(1.13f)
{
}

CMinion::CMinion(const CMinion & minion) :
	CMoveObj(minion)
{
	m_eDir = minion.m_eDir;
	m_fFireTime = minion.m_fFireTime;
	m_fFireLimitTime = minion.m_fFireLimitTime;
}


CMinion::~CMinion()
{
}

bool CMinion::Init()
{
	SetPos(800.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(300.f);

	m_eDir = MD_FRONT;

	return true;
}

int CMinion::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	MoveYFromSpeed(fDeltaTime, m_eDir);

	if (m_tPos.y + m_tSize.y >= GETRESOLUTION.iH) {
		m_tPos.y = GETRESOLUTION.iH - m_tSize.y;
		m_eDir = MD_BACK;
	}
	else if (m_tPos.y <= 0.f) {
		m_tPos.y = 0.f;
		m_eDir = MD_FRONT;
	}

	m_fFireTime += fDeltaTime;

	if (m_fFireTime >= m_fFireLimitTime)
	{
		m_fFireTime -= m_fFireLimitTime;
		Fire();
	}

	return 0;
}

int CMinion::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMinion::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CMinion::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
	Rectangle(hDC, (int)m_tPos.x, (int)m_tPos.y, (int)(m_tPos.x + m_tSize.x), (int)(m_tPos.y + m_tSize.y));
}

CMinion * CMinion::Clone()
{
	return new CMinion(*this);
}

void CMinion::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "MinionBullet",
		/*m_pScene->GetSceneType(),*/ m_pLayer);

	//pBullet->AddCollisionFunction("Bullet", CS_STAY, (CBullet*)pBullet, &CBullet::Hit);

	((CMoveObj*)pBullet)->SetAngle(PI);

	//float x = GetLeft() - (pBullet->GetSize().x * (1.f - GetPivot().x));
	//float y = GetCenter().y;
	pBullet->SetPos(m_tPos.x - pBullet->GetSize().x, (m_tPos.y + m_tPos.y + m_tSize.y) / 2.f - pBullet->GetSize().y / 2.f);
	//pBullet->SetPos(x, y);

	SAFE_RELEASE(pBullet);
}