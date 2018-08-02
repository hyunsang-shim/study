// WINAPI_2D.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WINAPI_2D.h"
#include "cManager.h"
#pragma comment(lib, "msimg32.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
cManager *Mgr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
RECT RectView;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void UpdateScene(HWND hWnd, HDC hdc);

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
		//SetTimer(hWnd, 1, 500, NULL);
		break;
    case WM_PAINT:
        {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);	
		UpdateScene(hWnd, hdc);
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


void UpdateScene(HWND hWnd, HDC hdc)
{
	HDC mDC = CreateCompatibleDC(hdc);
	HDC mDC_back = CreateCompatibleDC(hdc);
	BITMAP bit, btn1, btn2, btn3;
	BITMAP txt1, txt2;

	HBITMAP BG;
	HBITMAP btnStart, btnLoad, btnQuit;
	HBITMAP title1, title2;

	BG = (HBITMAP)LoadImage(NULL, TEXT(".\\Resources\\Scene\\Title\\title.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(BG, sizeof(BITMAP), &bit);

	btnStart = (HBITMAP)LoadImage(NULL, TEXT(".\\Resources\\Scene\\Title\\btn_new.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);

	btnLoad = (HBITMAP)LoadImage(NULL, TEXT(".\\Resources\\Scene\\Title\\btn_load.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	btnQuit = (HBITMAP)LoadImage(NULL, TEXT(".\\Resources\\Scene\\Title\\btn_quit.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	title1 = (HBITMAP)LoadImage(NULL, TEXT(".\\Resources\\Scene\\Title\\title_text1.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);

	title2 = (HBITMAP)LoadImage(NULL, TEXT(".\\Resources\\Scene\\Title\\title_text2.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);

	HBITMAP backBit = CreateCompatibleBitmap(mDC_back, RectView.right, RectView.bottom);

	HBITMAP oldBit = (HBITMAP)SelectObject(mDC_back, BG);

	if (btnStart == NULL)
	{
		MessageBox(hWnd, _T("파일을 불러오지 못했습니다."), _T("파일 읽어오기 실패"), MB_OK);
		PostQuitMessage(0);
	}

	TransparentBlt(mDC_back, 0, 0, RectView.right, RectView.bottom, mDC, 0, 0, RectView.right, RectView.bottom, RGB(255, 0, 255));

	BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, mDC_back, 0, 0, SRCCOPY);

	GetObject(btnStart, sizeof(BITMAP), &btn1);
	oldBit = (HBITMAP)SelectObject(mDC_back, btnStart);
	TransparentBlt(mDC_back, 600, 400, 185, 60, mDC, 0, 0, 185, 60, RGB(255, 0, 255));

	BitBlt(hdc, 600, 370, 185, 60, mDC_back, 0, 0, SRCCOPY);
	
	GetObject(btnLoad, sizeof(BITMAP), &btn2);
	oldBit = (HBITMAP)SelectObject(mDC_back, btnLoad);
	TransparentBlt(mDC_back, 600, 450, 185, 60, mDC, 0, 0, 185, 60, RGB(255, 0, 255));

	BitBlt(hdc, 600, 450, 185, 60, mDC_back, 0, 0, SRCCOPY);

	GetObject(btnQuit, sizeof(BITMAP), &btn3);
	oldBit = (HBITMAP)SelectObject(mDC_back, btnQuit);
	TransparentBlt(mDC_back, 607, 570, 185, 60, mDC, 0, 0, 185, 60, RGB(255, 0, 255));


	BitBlt(hdc, 600, 530, 185, 60, mDC_back, 0, 0, SRCCOPY);

	GetObject(title1, sizeof(BITMAP), &txt1);
	oldBit = (HBITMAP)SelectObject(mDC_back, title1);
	TransparentBlt(mDC_back, 245, 0, 344, 96, mDC, 0, 0, 344, 96, RGB(255, 0, 255));


	BitBlt(hdc, 245, 0, 185, 60, mDC_back, 0, 0, SRCCOPY);

	GetObject(title2, sizeof(BITMAP), &txt2);
	oldBit = (HBITMAP)SelectObject(mDC_back, title2);
	TransparentBlt(mDC_back, 245, 97, 344, 96, mDC, 0, 0, 344, 96, RGB(255, 0, 255));


	BitBlt(hdc, 245, 97, 185, 60, mDC_back, 0, 0, SRCCOPY);

	//TransparentBlt(hdc, 0, 0, RectView.right, RectView.bottom, mDC, 0, 0, RectView.right, RectView.bottom, RGB(255, 0, 255));
	//BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, mDC, 0, 0, SRCCOPY);

	SelectObject(mDC, oldBit);
	DeleteObject(backBit);
	DeleteDC(mDC);



}