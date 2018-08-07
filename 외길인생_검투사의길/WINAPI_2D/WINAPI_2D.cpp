// WINAPI_2D.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WINAPI_2D.h"
#include "cManager.h"
#include "SceneManager.h"
#include "cTownScene.h"
#include "cTitleScene.h"
#pragma comment(lib, "msimg32.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

RECT RectView;
cManager *Mgr = new cManager();
DWORD dwStart, dwEnd;


SceneManager *ScnMgr = new SceneManager();
cTownScene *ScnTown = new cTownScene();
cTitleScene *scnTitle = new cTitleScene();


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void UpdateScene(HDC hdc, int SceneName);
void DrawTitleScene(HDC hdc);
void DrawTownScene(HDC hdc);
void DrawBattleScene(HDC hdc);
bool HaveSaveFile();


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
    LoadStringW(hInstance, IDC_WINAPI2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2D));

    MSG msg;

    // 기본 메시지 루프입니다.
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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, 
	   SCREEN_WIDTH + (GetSystemMetrics(SM_CXFRAME)>>1), SCREEN_HEIGHT + (GetSystemMetrics(SM_CYFRAME)<<1) + GetSystemMetrics(SM_CYCAPTION) ,
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		Mgr->GetInstance();
		GetClientRect(hWnd, &RectView);
		scnTitle->LoadScene(hInst, GetDC(hWnd));
		SetTimer(hWnd, 1, (1000/60), NULL);
		break;
    case WM_PAINT:
        {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		scnTitle->DrawTitleScene(hdc);
		EndPaint(hWnd, &ps);
		SetTimer(hWnd, 1, (1000 / 60), NULL);
        }
        break;
	case WM_TIMER:
		KillTimer(hWnd, 1);
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;		
	case WM_MOVE:
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_UP:
			if (scnTitle->GetCurMenu() == menuNew)
				scnTitle->SetCurMenu(menuQuit);
			else if (scnTitle->GetCurMenu() == menuQuit)
				if (HaveSaveFile())
					scnTitle->SetCurMenu(menuLoad);
				else
					scnTitle->SetCurMenu(menuNew);
			else
				scnTitle->SetCurMenu(menuNew);

			InvalidateRgn(hWnd, NULL, FALSE);

			break;
		case VK_DOWN:
			if (scnTitle->GetCurMenu() == menuNew)
				if (HaveSaveFile())
					scnTitle->SetCurMenu(menuLoad);
				else
					scnTitle->SetCurMenu(menuQuit);
			else if (scnTitle->GetCurMenu() == menuLoad)
				scnTitle->SetCurMenu(menuQuit);
			else
				scnTitle->SetCurMenu(menuNew);		

			InvalidateRgn(hWnd, NULL, FALSE);
			break;
		case VK_RETURN:
			switch (scnTitle->GetCurMenu())
			{
			case menuQuit:
				PostQuitMessage(0);
				break;
			}
			break;
		}
	break; 
	case WM_SETFOCUS:
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void UpdateScene(HDC hdc, int SceneName)
{
	

	// 배경 요소들을 그린다
	switch (SceneName)
	{
	case TitleScene:
		DrawTitleScene(hdc);				
		break;
	}
	// BG -> 버튼	
	// 캐릭터를 그린다
	// UI를 그린다

}


void DrawTitleScene(HDC hdc)
{	
	
	
}

void DrawTownScene(HDC hdc)
{
	
	
}

void DrawBattleScene(HDC hdc)
{
}

bool HaveSaveFile()
{
	return TRUE;
}