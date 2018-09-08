// MultiThread_exercise.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MultiThread_exercise.h"
#include <vector>
#include <time.h>
#include <process.h>
#include <vld.h>


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
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



#define THREAD_MAX 10
POINT Circles[THREAD_MAX];
HANDLE hThread[THREAD_MAX];
#define circle_size 30
HANDLE hEvent;
int i;
short aAliveThreads[THREAD_MAX] = { 0 };
void Thread_Proc(void *arg)
{		

	int idx = *((int*)arg);

	int add_x = 5;
	int add_y = 5;

	while (1)
	{		
		EnterCriticalSection(&crit);
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
		
		if (!aAliveThreads[idx] >= 2)
			break;
		else 
			Sleep(50);

	}
	
	return;
}
void DoSomething()
{
	int add_x = 5;
	int add_y = 5;
	int i = 0;

	for (i = 0; i < THREAD_MAX; i++)
	{
		Circles[i].x += add_x;
		Circles[i].y += add_y;

		if (Circles[i].x - circle_size / 2 < RectView.left)
		{
			add_x *= -1;
			Circles[i].x = RectView.left + circle_size / 2;
		}
		else if (Circles[i].x + circle_size / 2 > RectView.right)
		{
			add_x *= -1;
			Circles[i].x = RectView.right - circle_size / 2;
		}

		if (Circles[i].y - circle_size / 2 < RectView.top)
		{
			add_y *= -1;
			Circles[i].y = RectView.top + circle_size / 2;
		}
		else if (Circles[i].y + circle_size / 2 > RectView.bottom)
		{
			add_y *= -1;
			Circles[i].y = RectView.bottom - circle_size / 2;
		}
	}

}
void DrawCircles(HDC hdc)
{
	EnterCriticalSection(&crit);
	// Create Back Memory DC
	HDC BackMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(hWnd);
	HBITMAP hBit = CreateCompatibleBitmap(tmpDC, RectView.right, RectView.bottom);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit);
	ReleaseDC(hWnd, tmpDC);
	DeleteObject(hBit);
	

	static int rr;
	static int gg;
	static int bb;

	for (int i = 0; i < THREAD_MAX; i++)
	{
		rr = Circles[i].x % 256;
		gg = (Circles[i].x + Circles[i].y) % 256;
		bb = Circles[i].y % 256;

		HBRUSH MyBrush = CreateSolidBrush(RGB(rr, gg, bb));
		SelectObject(BackMemDC, MyBrush);
		Ellipse(BackMemDC, Circles[i].x - circle_size / 2, Circles[i].y - circle_size / 2, Circles[i].x + circle_size / 2, Circles[i].y + circle_size / 2);
		DeleteObject(MyBrush);

	}

	// Draw BackDC onto FrontDC
	BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, BackMemDC, 0, 0, SRCCOPY);

	SelectObject(BackMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);

	LeaveCriticalSection(&crit);

}


void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{	

	InvalidateRgn(hWnd, NULL, FALSE);

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
	
	int i = 0;

    switch (message)
    {   
	case WM_CREATE:
		GetClientRect(hWnd, &RectView);
		InitializeCriticalSection(&crit);
		SetTimer(hWnd, 1, 13, &TimerProc);
		break;
	case WM_LBUTTONDOWN:
	{					
		for (i = 0; i < THREAD_MAX; i++)
		{
			POINT tmp;
			tmp.x = rand() % RectView.right;
			tmp.y = rand() % RectView.bottom;

			Circles[i] = tmp;			
			int idx = i;
			aAliveThreads[idx] = 1;
			//hThread[idx] = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))Thread_Proc, (void *)&idx, 0, NULL);
			hThread[i] = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))Thread_Proc, (void *)&idx, 0, NULL);
			Sleep(50);
		}			
	}
		break;
	case WM_PAINT:
	{
		EnterCriticalSection(&crit); 
	
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		//DoSomething();
		DrawCircles(hdc);
		
		EndPaint(hWnd, &ps); 

		LeaveCriticalSection(&crit);
	}
		break;
	case WM_GETMINMAXINFO:
		GetClientRect(hWnd, &RectView);
		return 0;
    case WM_DESTROY:
		for (int i = 0; i < THREAD_MAX; i++)
		{
			aAliveThreads[i] = false;		
		}

		for (int i = 0; i < THREAD_MAX; i++)
		{			
			CloseHandle(hThread[i]);
		}

		KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
