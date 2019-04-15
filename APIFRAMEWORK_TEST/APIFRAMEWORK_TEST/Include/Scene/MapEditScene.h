#pragma once
#include "Scene.h"



class CMapEditScene :
	public CScene
{
private:
	friend class CSceneManager;

	CMapEditScene();
	~CMapEditScene();

	TILE_EDIT_MODE m_eTem;
	TILE_OPTION m_eEditOption;
	vector<class CTexture*> m_vecTileTex;
	int m_iEditTileTex;
	class CStage* m_pStage;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

};

