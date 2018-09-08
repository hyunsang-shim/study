// MultiThread_exercise.cpp: ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h"
#include "MultiThread_exercise.h"
#include <vector>
#include <time.h>
#include <process.h>
#include <vld.h>


#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE			hInst;                              // ���� �ν��Ͻ��Դϴ�.
WCHAR				szTitle[MAX_LOADSTRING];            // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR				szWindowClass[MAX_LOADSTRING];      // �⺻ â Ŭ���� �̸��Դϴ�.
HWND				hWnd;								// ������ �ڵ��� ��������ȭ
RECT RectView;
CRITICAL_SECTION	crit;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MULTITHREADEXERCISE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MULTITHREADEXERCISE));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
