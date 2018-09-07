// MultiThread_exercise.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MultiThread_exercise.h"
#include <vector>
#include <time.h>
#include <process.h>


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE			hInst;                              // 현재 인스턴스입니다.
WCHAR				szTitle[MAX_LOADSTRING];            // 제목 표시줄 텍스트입니다.
WCHAR				szWindowClass[MAX_LOADSTRING];      // 기본 창 클래스 이름입니다.
HWND				hWnd;								// 윈도우 핸들의 전역변수화
RECT RectView;
CRITICAL_SECTION	crit;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_MULTITHREADEXERCISE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MULTITHREADEXERCISE));

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



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MULTITHREADEXERCISE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}




std::vector<POINT> Circles;
#define circle_size 30

void Thread_Proc(void *arg)
{		
	EnterCriticalSection(&crit);

	int idx = *((int*)arg);

	int add_x = 3;
	int add_y = 3;

	while (1)
	{
		

		Circles[idx].x += add_x;
		Circles[idx].y += add_y;

		if (Circles[idx].x - circle_size/2 < RectView.left)
		{
			add_x *= -1;
			Circles[idx].x = RectView.left + circle_size/2;
		}
		else if (Circles[idx].x + circle_size / 2 > RectView.right)
		{
			add_x *= -1;
			Circles[idx].x = RectView.right - circle_size/2;
		}

		if (Circles[idx].y - circle_size / 2 < RectView.top)
		{
			add_y *= -1;
			Circles[idx].y = RectView.top + circle_size/2;
		}
		else if (Circles[idx].y + circle_size / 2 > RectView.bottom)
		{
			add_y *= -1;
			Circles[idx].y = RectView.bottom - circle_size/2;
		}
		
		LeaveCriticalSection(&crit);

		Sleep(50);
	}
	
	return;
}

void DrawCircles(HDC hdc)
{
	// Create Back Memory DC
	HDC BackMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(hWnd);
	HBITMAP hBit = CreateCompatibleBitmap(hdc, RectView.right, RectView.bottom);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit);
	SelectObject(BackMemDC, GetStockObject(WHITE_BRUSH));
	Rectangle(BackMemDC, RectView.left, RectView.top, RectView.right, RectView.bottom);
	ReleaseDC(hWnd, tmpDC);
	DeleteObject(hBit);

	for (int i = 0; i < Circles.size(); i++)
	{
		int rr = Circles[i].x % 256;
		int gg = (Circles[i].x % 256 + Circles[i].y % 256) % 256;
		int bb = Circles[i].y % 256;

		SelectObject(BackMemDC, CreateSolidBrush(RGB(rr, gg, bb)));
		Ellipse(BackMemDC, Circles[i].x - circle_size / 2, Circles[i].y - circle_size / 2, Circles[i].x + circle_size / 2, Circles[i].y + circle_size / 2);
	}

	BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, BackMemDC, 0, 0, SRCCOPY);
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static std::vector<HANDLE> hThread;

	int i = 0;

    switch (message)
    {   
	case WM_CREATE:
		GetClientRect(hWnd, &RectView);
		InitializeCriticalSection(&crit);
		SetTimer(hWnd, 1, 10, NULL);
		break;
    case WM_PAINT:
        {

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			DrawCircles(hdc);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
			LeaveCriticalSection(&crit);

        }
        break;
	case WM_LBUTTONDOWN:
	{
		for (int i = 0; i < 10; i++)
		{
			POINT tmp;
			tmp.x = rand() % RectView.right;
			tmp.y = rand() % RectView.bottom;

			Circles.push_back(tmp);
			int idx = i;
			hThread.push_back((HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))Thread_Proc, (void *)&idx, 0, NULL));
			Sleep(30);
		}	
	}
		break;
	case WM_TIMER:
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
    case WM_DESTROY:
		for (int i = 0; i < hThread.size(); i++)
			CloseHandle(hThread[i]);
		DeleteCriticalSection(&crit);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
