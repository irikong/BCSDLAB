#include "Tile.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"

CTile::CTile() : m_eOption(TO_NONE)
{
	m_pOptionTex = GET_SINGLE(CResourcesManager)->FindTexture("TileNone");
}

CTile::CTile(const CTile & tile) : CStaticObj(tile)
{
	m_eOption = tile.m_eOption;
	m_pOptionTex = tile.m_pOptionTex;

	if (m_pOptionTex)
		m_pOptionTex->AddRef();
}


CTile::~CTile()
{
	SAFE_RELEASE(m_pOptionTex);
}

bool CTile::Init()
{
	return true;
}

void CTile::Input(float fDeltaTime)
{
	CStaticObj::Input(fDeltaTime);
}

int CTile::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	return 0;
}

int CTile::LateUpdate(float fDeltaTime)
{
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CTile::Collision(float fDeltaTime)
{
	CStaticObj::Collision(fDeltaTime);
}

void CTile::Render(HDC hDC, float fDeltaTime)
{
	CStaticObj::Render(hDC, fDeltaTime);

	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();

	RESOLUTION tClientRS = GET_SINGLE(CCamera)->GetCllientRS();

	bool bInClient = true;

	if (tPos.x + m_tSize.x < 0)
		bInClient = false;

	else if (tPos.x > tClientRS.iW)
		bInClient = false;

	else if (tPos.y + m_tSize.y < 0)
		bInClient = false;

	else if (tPos.y > tClientRS.iH)
		bInClient = false;

	if (m_pTexture && bInClient) {
		POSITION tImagePos;

		tImagePos += m_tImageOffset;

		if (m_pOptionTex->GetColorKeyEnable()) {
			TransparentBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_tSize.x, (int)m_tSize.y,
				m_pOptionTex->GetDC(), (int)tImagePos.x, (int)tImagePos.y, (int)m_tSize.x, (int)m_tSize.y, m_pOptionTex->GetColorKey());
		}
		else {
			BitBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_tSize.x, (int)m_tSize.y,
				m_pOptionTex->GetDC(), (int)tImagePos.x, (int)tImagePos.y, SRCCOPY);
		}
	}
}

CTile * CTile::Clone()
{
	return new CTile(*this);
}

void CTile::Save(FILE * pFile)
{
	CStaticObj::Save(pFile);

	fwrite(&m_eOption, 4, 1, pFile);
}

void CTile::Load(FILE * pFile)
{
	CStaticObj::Load(pFile);

	fread(&m_eOption, 4, 1, pFile);

	SetTileOption(m_eOption);
}

void CTile::SetTileOption(TILE_OPTION eOption)
{
	m_eOption = eOption;
	SAFE_RELEASE(m_pOptionTex);

	switch (eOption) {
	case TO_NONE:
		m_pOptionTex = GET_SINGLE(CResourcesManager)->FindTexture("TileNone");
		break;
	case TO_NOMOVE:
		m_pOptionTex = GET_SINGLE(CResourcesManager)->FindTexture("TileNoMove");
		break;
	}
}