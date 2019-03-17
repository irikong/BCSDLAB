// WINAPI_TEST.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WINAPI_TEST.h"
#include <list>
#include <cmath>

using namespace std;

#define MAX_LOADSTRING 100

enum MOVE_DIR {
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};

typedef struct _tagRectangle {
	float l, t, r, b;
}RECTANGLE, *PRECTANGLE;

typedef struct _tagSphere {
	float x, y;
	float r;
}SPHERE, *PSPHERE;

typedef struct _tagBullet {
	SPHERE tSphere;
	float fDist;
	float fLimitDist;
	float fAngle;
}BULLET, *PBULLET;

typedef struct _tagMonster {
	SPHERE tSphere;
	float fSpeed;
	float fTime;
	float fLimitTime;
	int iDir;
}MONSTER, *PMONSTER;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;
HDC g_hDC;
bool g_bLoop = true;
SPHERE g_tPlayer = { 50.f, 50.f, 50.f };
POINT g_tGunPos;
float g_fGunLength = 70.f;
float g_fPlayerAngle;
MONSTER g_tMonster;
const int PI = 3.141592f;

// 플레이어 총알
list<BULLET> g_PlayerBulletList;

// 몬스터 총알
list<BULLET> g_MonsterBulletList;

// 시간을 구하기 위한 전역 변수:
LARGE_INTEGER g_tSecond;
LARGE_INTEGER g_tTime;
float g_fDeltaTime;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Run();

struct _tagArea {
	bool bStart;
	POINT ptStart;
	POINT ptEnd;
};

_tagArea g_tArea;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPITEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	g_hDC = GetDC(g_hWnd); // 화면용 DC 생성

	// 몬스터 초기화
	g_tMonster.tSphere.x = 800.f - 50.f;
	g_tMonster.tSphere.y = 50.f;
	g_tMonster.tSphere.r = 50.f;
	g_tMonster.fSpeed = 300.f;
	g_tMonster.fTime = 0.f;
	g_tMonster.fLimitTime = 1.3f;
	g_tMonster.iDir = MD_FRONT;

	// 플레이어 총구의 위치를 구해줍니다.
	g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle) * g_fGunLength;
	g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle) * g_fGunLength;


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPITEST));

	MSG msg;

	QueryPerformanceFrequency(&g_tSecond);
	QueryPerformanceCounter(&g_tTime);

	// 기본 메시지 루프입니다:
	while (g_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else {
			Run();
		}
	}

	ReleaseDC(g_hWnd, g_hDC);

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPITEST));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_WINAPITEST);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_LBUTTONDOWN: // 마우스 왼쪽 버튼이 눌렸을 때
		// 마우스의 위치는 lParam에 들어옵니다. 각각 16비트로 쪼개져서 x, y 값이 32비트 변수에 들어옵니다.
		// LOWORD, HIWORD 매크로를 이용하여 하위, 상위 16비트의 값을 얻어올 수 있습니다.
		if (!g_tArea.bStart) {
			g_tArea.bStart = true;
			g_tArea.ptStart.x = lParam & 0x0000ffff;
			g_tArea.ptStart.y = lParam >> 16;
			g_tArea.ptEnd = g_tArea.ptStart;

			InvalidateRect(hWnd, nullptr, TRUE); // InvalidatRect 함수는 WM_PAINT 메세지를 강제로 호출해주는 함수입니다.
												 // 1번 인자 : 윈도우 핸들, 2번 인자 : 초기화할 영역(NULL을 넣을 경우 전체 화면)
												 // 3번 인자 : TRUE일 경우 현재 화면을 지우고 갱신하며 FALSE일 경우 현재 화면을 지우지 않고 갱신
		}
		break;
	case WM_MOUSEMOVE: // 마우스가 움직일 때
		if (g_tArea.bStart) {
			g_tArea.ptEnd.x = lParam & 0x0000ffff;
			g_tArea.ptEnd.y = lParam >> 16;
			InvalidateRect(hWnd, nullptr, TRUE);
		}
		break;
	case WM_LBUTTONUP: // 마우스 왼쪽 버튼이 올라왔을 때
		if (g_tArea.bStart) {
			g_tArea.bStart = false;
			g_tArea.ptEnd.x = lParam & 0x0000ffff;
			g_tArea.ptEnd.y = lParam >> 16;
			InvalidateRect(hWnd, nullptr, TRUE);
		}
		break;
	case WM_KEYDOWN: // 키가 눌렸을 때
		switch (wParam) { // wParam에 어떤 키가 눌렸는지 들어옵니다.
		case VK_ESCAPE: // wParam == ESC 일 때
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		TextOut(hdc, 50, 0, L"BCSDLAB", 7); // 유니코드 문자열은 "" 앞에 L을 붙여줍니다.
		TextOut(hdc, 50, 20, TEXT("WinAPI"), 6); // TEXT 매크로를 사용하면 멀티바이트와 유니코드를 알아서 처리해줍니다.

		TCHAR strMouse[64] = {};
		wsprintf(strMouse, TEXT("Startx : %d, Starty : %d"), g_tArea.ptStart.x, g_tArea.ptStart.y); // wsprintf : 유니코드 문자열 생성 함수
		TextOut(hdc, 600, 50, strMouse, lstrlen(strMouse)); // lstrlen : 유니코드 문자열의 길이를 구해주는 함수

		Ellipse(hdc, 75, 75, 225, 225);

		Rectangle(hdc, 100, 100, 200, 200);

		Ellipse(hdc, 100, 100, 200, 200);

		MoveToEx(hdc, 300, 300, nullptr);
		LineTo(hdc, 400, 400);
		LineTo(hdc, 500, 300);

		MoveToEx(hdc, 100, 300, nullptr);
		LineTo(hdc, 200, 400);
		LineTo(hdc, 300, 300);

		if (g_tArea.bStart) {
			Rectangle(hdc, g_tArea.ptStart.x, g_tArea.ptStart.y, g_tArea.ptEnd.x, g_tArea.ptEnd.y);
		}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		g_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void Run() {
	// DeltaTime을 구해줍니다.
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);

	g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / (float)g_tSecond.QuadPart;

	g_tTime = tTime;

	static float fTimeScale = 1.f;
	if (GetAsyncKeyState(VK_F1) & 0x8000) { // F1키 누를 시 전체 속도 감소
		fTimeScale -= g_fDeltaTime;

		if (fTimeScale < 0.f) fTimeScale = 0.f;
	}
	if (GetAsyncKeyState(VK_F2) & 0x8000) { // F2키 누를 시 전체 속도 증가
		fTimeScale += g_fDeltaTime;

		if (fTimeScale > 1.f) fTimeScale = 1.f;
	}

	// 초당 이동속도
	float fSpeed = 300.f * g_fDeltaTime * fTimeScale;

	if (GetAsyncKeyState('D') & 0x8000) {
		g_fPlayerAngle += PI * g_fDeltaTime * fTimeScale;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		g_fPlayerAngle -= PI * g_fDeltaTime * fTimeScale;
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		g_tPlayer.x += fSpeed * cosf(g_fPlayerAngle);
		g_tPlayer.y += fSpeed * sinf(g_fPlayerAngle);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		g_tPlayer.x -= fSpeed * cosf(g_fPlayerAngle);
		g_tPlayer.y -= fSpeed * sinf(g_fPlayerAngle);
	}

	// 총구 위치를 구해줍니다.
	g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle) * g_fGunLength;
	g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle) * g_fGunLength;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		BULLET tBullet;

		tBullet.tSphere.x = g_tGunPos.x + cosf(g_fPlayerAngle) * 25.f;
		tBullet.tSphere.y = g_tGunPos.y + sinf(g_fPlayerAngle) * 25.f;
		tBullet.tSphere.r = 25.f;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 500.f;
		tBullet.fAngle = g_fPlayerAngle;

		g_PlayerBulletList.push_back(tBullet);
	}

	if (GetAsyncKeyState('1') & 0x8000) {
		float fAngle = g_fPlayerAngle - PI / 12.f;

		for (int i = 0; i < 3; i++) {
			BULLET tBullet;

			tBullet.tSphere.x = g_tGunPos.x + cosf(fAngle) * 25.f;
			tBullet.tSphere.y = g_tGunPos.y + sinf(fAngle) * 25.f;
			tBullet.tSphere.r = 25.f;
			tBullet.fDist = 0.f;
			tBullet.fLimitDist = 500.f;
			tBullet.fAngle = fAngle;

			g_PlayerBulletList.push_back(tBullet);

			fAngle += PI / 12.f;
		}
	}

	if (GetAsyncKeyState('2') & 0x8000) {
		float fAngle = 0.f;

		for (int i = 0; i < 30; i++) {
			BULLET tBullet;

			tBullet.tSphere.x = g_tGunPos.x + cosf(fAngle) * 25.f;
			tBullet.tSphere.y = g_tGunPos.y + sinf(fAngle) * 25.f;
			tBullet.tSphere.r = 25.f;
			tBullet.fDist = 0.f;
			tBullet.fLimitDist = 500.f;
			tBullet.fAngle = fAngle;

			g_PlayerBulletList.push_back(tBullet);

			fAngle += PI / 12.f;
		}
	}

	RECT rcWindow;
	GetClientRect(g_hWnd, &rcWindow);
	SetRect(&rcWindow, 0, 0, 800, 600);

	/*if (g_tPlayerRC.l < rcWindow.left) {
		g_tPlayerRC.l = (float)rcWindow.left;
		g_tPlayerRC.r = (float)rcWindow.left + 100;
	}
	else if (g_tPlayerRC.r > rcWindow.right) {
		g_tPlayerRC.l = (float)rcWindow.right - 100;
		g_tPlayerRC.r = (float)rcWindow.right;
	}
	if (g_tPlayerRC.t < rcWindow.top) {
		g_tPlayerRC.t = (float)rcWindow.top;
		g_tPlayerRC.b = (float)rcWindow.top + 100;
	}
	else if (g_tPlayerRC.b > rcWindow.bottom) {
		g_tPlayerRC.t = (float)rcWindow.bottom - 100;
		g_tPlayerRC.b = (float)rcWindow.bottom;
	}*/

	// 몬스터 이동
	g_tMonster.tSphere.y += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;
	//g_tMonster.tSphere.b += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;

	if (g_tMonster.tSphere.y + g_tMonster.tSphere.r >= 600) {
		g_tMonster.iDir = MD_BACK;
		g_tMonster.tSphere.y = 550;
	}
	else if (g_tMonster.tSphere.y - g_tMonster.tSphere.r <= 0) {
		g_tMonster.iDir = MD_FRONT;
		g_tMonster.tSphere.y = 50;
	}

	// 몬스터 총알 이동
	g_tMonster.fTime += g_fDeltaTime * fTimeScale;
	if (g_tMonster.fTime >= g_tMonster.fLimitTime) {
		g_tMonster.fTime -= g_tMonster.fLimitTime;

		BULLET tBullet = {};

		tBullet.tSphere.x = g_tMonster.tSphere.x - g_tMonster.tSphere.r - 25.f;
		tBullet.tSphere.y = g_tMonster.tSphere.y;
		tBullet.tSphere.r = 25.f;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 800.f;

		g_MonsterBulletList.push_back(tBullet);
	}

	// 플레이어 총알 이동
	list<BULLET>::iterator iter;
	list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();

	fSpeed = 600.f * g_fDeltaTime * fTimeScale;

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd;) {
		(*iter).tSphere.x += cosf((*iter).fAngle) * fSpeed;
		(*iter).tSphere.y += sinf((*iter).fAngle) * fSpeed;
		(*iter).fDist += fSpeed;

		float fX = (*iter).tSphere.x - g_tMonster.tSphere.x;
		float fY = (*iter).tSphere.y - g_tMonster.tSphere.y;
		float fDist = sqrtf((fX * fX) + (fY * fY));

		if (fDist <= (*iter).tSphere.r + g_tMonster.tSphere.r) {
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		else if ((*iter).fDist >= (*iter).fLimitDist) {
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else if ((*iter).tSphere.x - (*iter).tSphere.r >= 800) {
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else {
			++iter;
		}
	}

	// 몬스터 총알 이동
	iterEnd = g_MonsterBulletList.end();
	for (iter = g_MonsterBulletList.begin(); iter != iterEnd;) {
		(*iter).tSphere.x -= fSpeed;

		(*iter).fDist += fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist) {
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}
		else if ((*iter).tSphere.x + (*iter).tSphere.r <= 0) {
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}
		/*else if (g_tPlayerRC.l <= (*iter).rc.r && (*iter).rc.l <= g_tPlayerRC.r && g_tPlayerRC.t <= (*iter).rc.b && (*iter).rc.t <= g_tPlayerRC.b) {
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}*/
		else {
			++iter;
		}
	}

	Ellipse(g_hDC, g_tPlayer.x - g_tPlayer.r, g_tPlayer.y - g_tPlayer.r, g_tPlayer.x + g_tPlayer.r, g_tPlayer.y + g_tPlayer.r);
	Ellipse(g_hDC, g_tMonster.tSphere.x - g_tMonster.tSphere.r, g_tMonster.tSphere.y - g_tMonster.tSphere.r,
		g_tMonster.tSphere.x + g_tMonster.tSphere.r, g_tMonster.tSphere.y + g_tMonster.tSphere.r);

	MoveToEx(g_hDC, g_tPlayer.x, g_tPlayer.y, NULL);
	LineTo(g_hDC, g_tGunPos.x, g_tGunPos.y);

	iterEnd = g_PlayerBulletList.end();
	for (iter = g_PlayerBulletList.begin(); iter != iterEnd; iter++) {
		Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.r, (*iter).tSphere.y - (*iter).tSphere.r,
			(*iter).tSphere.x + (*iter).tSphere.r, (*iter).tSphere.y + (*iter).tSphere.r);
	}
	iterEnd = g_MonsterBulletList.end();
	for (iter = g_MonsterBulletList.begin(); iter != iterEnd; iter++) {
		Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.r, (*iter).tSphere.y - (*iter).tSphere.r,
			(*iter).tSphere.x + (*iter).tSphere.r, (*iter).tSphere.y + (*iter).tSphere.r);
	}
}