#pragma once
#include "Scene.h"

class CMapEditScene :
	public CScene
{
private:
	friend class CSceneManager;

	CMapEditScene();
	~CMapEditScene();

	vector<class CTexture*> m_vecTileTex;
	class CStage* m_pStage;

	TILE_EDIT_MODE	m_eTem;
	TILE_OPTION		m_eEditOption;
	int				m_iEditTileTex;
	

	static wchar_t m_strText[MAX_PATH];

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

