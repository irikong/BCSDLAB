#include "Player.h"



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

bool CPlayer::Init()
{
	return true;
}

void CPlayer::Input(float fDeltaTime)
{
}

int CPlayer::Update(float fDeltaTime)
{
	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	Rectangle(hDC, (int)m_tPos.x, (int)m_tPos.y, (int)(m_tPos.x + m_tSize.x), (int)(m_tPos.y + m_tSize.y));
}