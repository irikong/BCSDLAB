// WINAPI_TEST.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WINAPI_TEST.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPITEST));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPITEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL; //MAKEINTRESOURCEW(IDC_WINAPITEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
												 // 1번 인자 : 윈도우 핸들, 2번 인자 : 초기화할 영역(NULL을 넣을 경우 전체 화면),
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
