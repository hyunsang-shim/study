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
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
RECT RectView;
cManager *Mgr = new cManager();

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
void UpdateSelector();
bool HaveSaveFile();
void DrawSelector(HDC hdc);


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
	   SCREEN_WIDTH + (GetSystemMetrics(SM_CXFRAME)>>1), SCREEN_HEIGHT + (GetSystemMetrics(SM_CYFRAME)<<2) + GetSystemMetrics(SM_CYCAPTION) ,
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
	//static cManager *Mgr = new cManager();

	
    switch (message)
    {
	case WM_CREATE:
		Mgr->GetInstance();
		GetClientRect(hWnd, &RectView);
		SetTimer(hWnd, 1, 15, NULL);
		break;
    case WM_PAINT:
        {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		UpdateScene(hdc, Mgr->GetCurScene());
		switch (Mgr->GetCurScene())
		{
		case TitleScene:
			TextOut(hdc, 100, 100, _T("타이틀 화면입니다."), lstrlen(_T("타이틀 화면입니다.")));
			break;
		case BattleScene:
			TextOut(hdc, 100, 100, _T("배틀 화면입니다."), lstrlen(_T("배틀 화면입니다.")));
			break;
		case TownScene:
			TextOut(hdc, 100, 100, _T("타운 화면입니다."), lstrlen(_T("배틀 화면입니다.")));
			break;

		}
		EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;				
	case WM_RBUTTONDOWN:
		Mgr->SetCurScene(TownScene);	
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		Mgr->SetCurScene(TitleScene);		
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_MBUTTONDOWN:
		Mgr->SetCurScene(BattleScene);
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_UP:
			if (Mgr->GetCurMenu() == menuNew)
				Mgr->SetCurMenu(menuQuit);
			else if (Mgr->GetCurMenu() == menuQuit)
				if (HaveSaveFile())
					Mgr->SetCurMenu(menuLoad);
				else
					Mgr->SetCurMenu(menuNew);
			else
				Mgr->SetCurMenu(menuNew);

			UpdateSelector();
			break;
		case VK_DOWN:
			if (Mgr->GetCurMenu() == menuNew)
				if (HaveSaveFile())
					Mgr->SetCurMenu(menuLoad);
				else
					Mgr->SetCurMenu(menuQuit);
			else if (Mgr->GetCurMenu() == menuLoad)
				Mgr->SetCurMenu(menuQuit);
			else
				Mgr->SetCurMenu(menuNew);

			UpdateSelector();
			break;
		case VK_RETURN:
			switch (Mgr->GetCurMenu())
			{
			case menuQuit:
				PostQuitMessage(0);
				break;
			}
			break;
		}
	break; 
	case WM_SETFOCUS:
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void UpdateScene(HDC hdc, int SceneName)
{
	DWORD dwStart, dwEnd;
	TCHAR a[64] = {0,};
	dwStart = GetTickCount();

	
	
	// 배경 요소들을 그린다
	switch (SceneName)
	{
	case TitleScene:
		DrawTitleScene(hdc);
		dwEnd = GetTickCount();
		dwEnd -= dwStart;
		wsprintf(a, _T("종료 : + %dms"), dwEnd);
		TextOut(hdc, 10, 30, a, sizeof(a));
		UpdateSelector();
		break;
	}
	// BG -> 버튼	
	// 캐릭터를 그린다
	// UI를 그린다

}


void DrawTitleScene(HDC hdc)
{
	
	HDC BackMemDC, memDC;
	static HBRUSH hbrush;
	static HBITMAP hWorkBitmap;
	static HBITMAP hOldBitmap;
	BackMemDC = CreateCompatibleDC(hdc);
	memDC = CreateCompatibleDC(hdc);
	hbrush = CreateSolidBrush(RGB(255, 0, 255));

	hWorkBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hWorkBitmap);
	FillRect(BackMemDC, &RectView, (HBRUSH)hbrush);

	hWorkBitmap = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	(HBITMAP)SelectObject(memDC, hWorkBitmap);

	//Draw BG image onto BackMemDC
	BitBlt(BackMemDC, 0, 0, RectView.right, RectView.bottom, memDC, 0, 0, SRCCOPY);

	//Select and Draw Title Text1 onto BackMemDC
	hWorkBitmap = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\title_text1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hOldBitmap = (HBITMAP)SelectObject(memDC, hWorkBitmap);
	TransparentBlt(BackMemDC, 245, 0, 344, 96, memDC, 0, 0, 344, 96, RGB(255, 0, 255));

	//Select and Draw Title Text2 onto BackMemDC
	hWorkBitmap = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\title_text2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hOldBitmap = (HBITMAP)SelectObject(memDC, hWorkBitmap);
	TransparentBlt(BackMemDC, 245, 96, 344, 96, memDC, 0, 0, 344, 96, RGB(255, 0, 255));
	

	//Select and Draw New Button onto BackMemDC
	hWorkBitmap = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\btn_new.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hOldBitmap = (HBITMAP)SelectObject(memDC, hWorkBitmap);
	TransparentBlt(BackMemDC, 600, 390, 146, 43, memDC, 0, 0, 146, 43, RGB(255, 0, 255));
	

	//Select and Draw Load Button onto BackMemDC
	if (HaveSaveFile())
		hWorkBitmap = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\btn_load_on.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	else
		hWorkBitmap = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\btn_load_off.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	hOldBitmap = (HBITMAP)SelectObject(memDC, hWorkBitmap);
	TransparentBlt(BackMemDC, 600, 460, 146, 43, memDC, 0, 0, 146, 43, RGB(255, 0, 255));
	//BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, BackMemDC, 0, 0, SRCCOPY);

	//Select and Draw Quit Button onto BackMemDC
	hWorkBitmap = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Scene\\Title\\btn_quit.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	
	hOldBitmap = (HBITMAP)SelectObject(memDC, hWorkBitmap);
	TransparentBlt(BackMemDC, 600, 530, 146, 43, memDC, 0, 0, 146, 43, RGB(255, 0, 255));

	DrawSelector(BackMemDC);

	
	// Draw BackmemDC bitmap onto main FrontDC
	BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, BackMemDC, 0, 0, SRCCOPY);

	//DeleteObject(SelectObject(BackMemDC, hOldBitmap));
	DeleteDC(BackMemDC);
	DeleteDC(memDC);
}


void UpdateSelector()
{
	static int cnt = 0;
	int frame = scnTitle->GetCurSelectorFrame();
	cnt++;

	if (cnt > 10)
	{
		frame++;
		cnt = 0;
	}

	if (frame > 3)
		frame = 0;
		
	scnTitle->SetCurSelectorFrame(frame);
}

void DrawSelector(HDC hdc)
{
	HDC memDC;
	static HBITMAP backBitMap = NULL;
	static HBRUSH hbrush;
	HBITMAP hWorkBitmap;
	HBITMAP hOldBitmap;
	memDC = CreateCompatibleDC(hdc);
	hbrush = CreateSolidBrush(RGB(255, 0, 255));

	hWorkBitmap = CreateCompatibleBitmap(hdc, 50, 50);
	hOldBitmap = (HBITMAP)SelectObject(memDC, hWorkBitmap);

	// load PC character sprites
	hWorkBitmap = (HBITMAP)LoadImage(hInst, _T(".\\Resources\\Character\\PC_walk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//Select and Draw Title Text1 onto BackMemDC
	hOldBitmap = (HBITMAP)SelectObject(memDC, hWorkBitmap);
	TransparentBlt(		hdc,	535, 390 + Mgr->GetCurMenu() * 70, 50, 50,		memDC,		50 * (scnTitle->GetCurSelectorFrame()), 100, 50, 45, 		RGB(255, 0, 255));

	DeleteObject(SelectObject(memDC, hOldBitmap));
	DeleteObject(hWorkBitmap);
	DeleteDC(memDC);

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