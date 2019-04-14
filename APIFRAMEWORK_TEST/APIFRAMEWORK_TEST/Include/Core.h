#pragma once

#include "Game.h"

class CCore
{
private:
	static CCore* m_pInst;

public:
	static CCore* GetInst() {
		if (!m_pInst)
			m_pInst = new CCore;
		return m_pInst;
	}

	static void DestroyInst() { SAFE_DELETE(m_pInst); }

private:
	CCore();
	~CCore();

	static bool m_bLoop;

	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;
	RESOLUTION m_tRS;

public:
	RESOLUTION GetResolution() const { return m_tRS; }

	HWND GetWindowHandle() const { return m_hWnd; }

	void DestroyGame() // 창 삭제
	{
		DestroyWindow(m_hWnd); // 실패할 경우 0 반환
	}

	bool Init(HINSTANCE hInst);
	int Run();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void Logic();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);

private:
	ATOM MyRegisterClass();
	BOOL Create();
};

