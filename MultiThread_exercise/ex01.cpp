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
int					cnt_circles = 0;

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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
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
