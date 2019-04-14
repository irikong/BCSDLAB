#include "UI.h"
#include "../Animation/Animation.h"
#include "../Resources/Texture.h"

CUI::CUI()
{
}

CUI::CUI(const CUI & ui) :
	CObj(ui)
{
}


CUI::~CUI()
{
}

void CUI::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CUI::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	return 0;
}

int CUI::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);

	return 0;
}

void CUI::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CUI::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture)
	{
		POSITION tImagePos;

		if (m_pAnimation)
		{
			pANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();
			if (pClip->eType == AT_ATLAS)
			{
				tImagePos.x = pClip->iFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->iFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		if (m_pTexture->GetColorKeyEnable())
		{
			TransparentBlt(hDC, (int)m_tPos.x, (int)m_tPos.y, (int)m_tSize.x, (int)m_tSize.y,
				m_pTexture->GetDC(), (int)tImagePos.x, (int)tImagePos.y,
				(int)m_tSize.x, (int)m_tSize.y, m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, (int)m_tPos.x, (int)m_tPos.y, (int)m_tSize.x, (int)m_tSize.y,
				m_pTexture->GetDC(), (int)tImagePos.x, (int)tImagePos.y, SRCCOPY);
		}
	}
	// �浹ü Render
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}

		else
			++iter;
	}
}