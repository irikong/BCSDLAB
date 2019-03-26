#include "Scene.h"
#include "Layer.h"

CScene::CScene()
{
	CLayer* pLayer = CreateLayer("Default");
	pLayer = CreateLayer("UI", INT_MAX); // iZOrder = INT_MAX로 항상 뒤로 가게합니다.
}


CScene::~CScene()
{
	Safe_Delete_VecList(m_LayerList);
}

CLayer * CScene::CreateLayer(const string & strTag, int iZOrder)
{
	CLayer* pLayer = new CLayer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);
	pLayer->SetScene(this); // CreateLayer를 호출한 Scene에 Layer를 속하게 하기 위해 this 사용

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2)
		m_LayerList.sort(CScene::LayerSort);

	return pLayer;
}

bool CScene::Init()
{
	return true;
}

bool CScene::LayerSort(CLayer* pL1, CLayer* pL2) {
	return (pL1->GetZOrder() < pL2->GetZOrder());
}