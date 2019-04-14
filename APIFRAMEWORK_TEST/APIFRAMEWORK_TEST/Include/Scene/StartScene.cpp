#include "StartScene.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPixel.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"
#include "SceneManager.h"
#include "InGameScene.h"
#include "MapEditScene.h"

CStartScene::CStartScene()
{
}


CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	// �θ� Scene Ŭ������ �ʱ�ȭ �Լ��� ȣ�����ش�.
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("UI");

	// ����ȭ�� ���
	CUIPanel* pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize((float)GETRESOLUTION.iW, (float)GETRESOLUTION.iH);
	pBackPanel->SetTexture("StartBack", L"StartBack.bmp");

	SAFE_RELEASE(pBackPanel);

	// ����ȭ�� ���۹�ư
	CUIButton* pStartBtn = CObj::CreateObj<CUIButton>("StartButton", pLayer);

	pStartBtn->SetPos((float)GETRESOLUTION.iW / 2 - 300, (float)GETRESOLUTION.iH / 2 + 50);
	pStartBtn->SetSize(200, 100);
	pStartBtn->SetTexture("StartButton", L"StartButton.bmp");

	CColliderRect* pRC = (CColliderRect*)pStartBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 200, 100);
	//pRC->AddCollisionFunction(CS_ENTER, pStartBtn, &CUIButton::MouseOn);
	//pRC->AddCollisionFunction(CS_LEAVE, pStartBtn, &CUIButton::MouseOut);

	SAFE_RELEASE(pRC);

	pStartBtn->SetCallback(this, &CStartScene::StartButtonCallback);

	SAFE_RELEASE(pStartBtn);


	// Edit ��ư

	CUIButton* pEditBtn = CObj::CreateObj<CUIButton>("EditButton", pLayer);

	pEditBtn->SetPos((float)GETRESOLUTION.iW / 2 - 100, (float)GETRESOLUTION.iH / 2 - 50);
	pEditBtn->SetSize(200, 100);
	pEditBtn->SetTexture("StartButton", L"StartButton.bmp");

	pRC = (CColliderRect*)pEditBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 200, 100);

	SAFE_RELEASE(pRC);

	pEditBtn->SetCallback(this, &CStartScene::EditButtonCallback);

	SAFE_RELEASE(pEditBtn);

	

	// ����ȭ�� �����ư
	CUIButton* pEndBtn = CObj::CreateObj<CUIButton>("EndButton", pLayer);

	pEndBtn->SetPos((float)GETRESOLUTION.iW / 2 + 100, (float)GETRESOLUTION.iH / 2 + 50);
	pEndBtn->SetSize(200, 100);
	pEndBtn->SetTexture("EndButton", L"EndButton.bmp");

	pRC = (CColliderRect*)pEndBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 200, 100);
	//pRC->AddCollisionFunction(CS_ENTER, pEndBtn, &CUIButton::MouseOn);
	//pRC->AddCollisionFunction(CS_LEAVE, pEndBtn, &CUIButton::MouseOut);

	SAFE_RELEASE(pRC);

	pEndBtn->SetCallback(this, &CStartScene::EndButtonCallback);

	SAFE_RELEASE(pEndBtn);

	return true;
}

void CStartScene::StartButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
}

void CStartScene::EndButtonCallback(float fTime)
{
	GET_SINGLE(CCore)->DestroyGame();
}

void CStartScene::EditButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CMapEditScene>(SC_NEXT);
}
