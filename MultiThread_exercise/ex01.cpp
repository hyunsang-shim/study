// MultiThread_exercise.cpp: ���� ���α׷��� �������� �����մϴ�.
//

#include "stdafx.h"
#include "MultiThread_exercise.h"
#include <vector>
#include <time.h>
#include <process.h>


#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE			hInst;                              // ���� �ν��Ͻ��Դϴ�.
WCHAR				szTitle[MAX_LOADSTRING];            // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR				szWindowClass[MAX_LOADSTRING];      // �⺻ â Ŭ���� �̸��Դϴ�.
HWND				hWnd;								// ������ �ڵ��� ��������ȭ
int					cnt_circles = 0;

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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

typedef struct circle_for_thread {
	int left;
	int top;
	int right;
	int bottom;
	int r;
	int g;
	int b;
}THREAD_CIRCLE;


HANDLE hEvent;
void Thread_Proc(void *args)
{
	HDC hdc;
	THREAD_CIRCLE circle = *((THREAD_CIRCLE*)args);	
	int r_plus, g_plus, b_plus;	
	r_plus = g_plus = b_plus = 5;

	int shown = 0;

	srand((unsigned)time(0));
	hdc = GetDC(hWnd);
	while (1)
	{
		SelectObject(hdc, CreateSolidBrush(RGB(circle.r, circle.g, circle.b)));		
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		
		Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom);
				
		circle.r += r_plus;
		circle.g += g_plus;
		circle.b += b_plus;


		if (circle.r >= 255)
		{
			r_plus *= -1;
			circle.r = 255;
		}
		else if (circle.r <= 0)
		{
			r_plus *= -1;
			circle.r = 0;
		}

		if (circle.g >= 255)
		{
			g_plus *= -1;
			circle.g = 255;
		}
		else if (circle.g <= 0)
		{
			g_plus *= -1;
			circle.g = 0;
		}

		if (circle.b >= 255)
		{
			b_plus *= -1;
			circle.b = 255;
		}
		else if (circle.b <= 0)
		{
			b_plus *= -1;
			circle.b = 0;
		}

		if (shown > 100)
		{
			SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			SelectObject(hdc, GetStockObject(WHITE_PEN));

			Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom);

			break;
		}
		else
			shown++;

		Sleep(80);
	}

	ReleaseDC(hWnd, hdc);
	return;
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
	static std::vector<THREAD_CIRCLE> args;
	static std::vector<HANDLE> hThread;

	static RECT RectView;
	THREAD_CIRCLE tmp;
	int i = 0;

    switch (message)
    {   
	case WM_CREATE:
		GetClientRect(hWnd, &RectView);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
	{
		tmp.left = rand()% RectView.right;
		tmp.top = rand()% RectView.bottom;
		tmp.right = tmp.left + 50;
		tmp.bottom = tmp.top + 50;
		tmp.r = rand() % 256;
		tmp.g = rand() % 256;
		tmp.b = rand() % 256;

		args.push_back(tmp);
		hThread.push_back((HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))Thread_Proc, (void *)&args[args.size() - 1], 0, NULL));
		cnt_circles++;
		Sleep(500);
	}
		break;
    case WM_DESTROY:
		for (int i = 0; i < hThread.size(); i++)
			CloseHandle(hThread[i]);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
