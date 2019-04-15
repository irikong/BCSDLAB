#include "MapEditScene.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "../Core/Input.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"

CMapEditScene::CMapEditScene()
{
	m_eTem = TEM_TEXTURE;
}


CMapEditScene::~CMapEditScene()
{
	Safe_Release_VecList(m_vecTileTex);
	SAFE_RELEASE(m_pStage);
}

bool CMapEditScene::Init()
{
	GET_SINGLE(CCamera)->SetWorldResolution(5200,5200);

	CTexture* pNoneTex = GET_SINGLE(CResourcesManager)->LoadTexture("TileNone", L"Tile/OptionNone.bmp");
	pNoneTex->SetColorKey(255, 0, 255);
	SAFE_RELEASE(pNoneTex);
	CTexture* pNoMoveTex = GET_SINGLE(CResourcesManager)->LoadTexture("TileNoMove", L"Tile/OptionNoMove.bmp");
	pNoMoveTex->SetColorKey(255, 0, 255);
	SAFE_RELEASE(pNoMoveTex);

	CLayer* pStageLayer = FindLayer("Stage");

	m_pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	m_pStage->CreateTile(100, 100, 52, 52, "BaseTile", L"Tile/BaseTile.bmp");

	CTexture* pTex = GET_SINGLE(CResourcesManager)->FindTexture("BaseTile");
	m_vecTileTex.push_back(pTex);

	pTex = GET_SINGLE(CResourcesManager)->LoadTexture("Tile1", L"Tile/Tile1.bmp");
	m_vecTileTex.push_back(pTex);

	pTex = GET_SINGLE(CResourcesManager)->LoadTexture("Tile2", L"Tile/Tile2.bmp");
	m_vecTileTex.push_back(pTex);

	m_iEditTileTex = 0;
	m_eEditOption = TO_NONE;

	return true;
}

void CMapEditScene::Input(float fDeltaTime)
{
	CScene::Input(fDeltaTime);

	if (GetAsyncKeyState('W') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(0.f, -300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(0.f, 300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(-300.f * fDeltaTime, 0);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(300.f * fDeltaTime, 0);
	}

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		m_eTem = TEM_TEXTURE;
	}
	if (GetAsyncKeyState(VK_F2) & 0x8000) {
		m_eTem = TEM_OPTION;
	}

	if (GetAsyncKeyState('1') & 0x8000) {
		switch (m_eTem) {
		case TEM_TEXTURE:
			m_iEditTileTex = 0;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NONE;
			break;
		}
	}
	if (GetAsyncKeyState('2') & 0x8000) {
		switch (m_eTem) {
		case TEM_TEXTURE:
			m_iEditTileTex = 1;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		}
	}
	if (GetAsyncKeyState('3') & 0x8000) {
		switch (m_eTem) {
		case TEM_TEXTURE:
			m_iEditTileTex = 2;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		}
	}

	if (KEYPRESS("MouseLButton")) {
		POSITION tMouseWorldPos = MOUSEWORLDPOS;

		switch (m_eTem) {
		case TEM_TEXTURE:
			m_pStage->ChangeTileTexture(tMouseWorldPos, m_vecTileTex[m_iEditTileTex]);
			break;
		case TEM_OPTION:
			m_pStage->ChangeTileOption(tMouseWorldPos, m_eEditOption);
			break;
		}
	}
	if (KEYPRESS("MouseRButton")) {

	}
}