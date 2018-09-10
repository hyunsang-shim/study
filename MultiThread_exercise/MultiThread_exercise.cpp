// MultiThread_exercise.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MultiThread_exercise.h"
#include <vector>
#include <time.h>
#include <process.h>
//#include <vld.h>


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



#define circle_size 30

typedef struct Balls {
	int id;
	int x;
	int y;
	bool isCollide;
	bool isAlive;
	short rrr;
	short ggg;
	short bbb;
	int speed_X;
	int speed_Y;
	
}BALL;

typedef struct Threads{
	int id;
	HANDLE handle;
	bool isAlive;
}THREADS;

int i; 
int speed_x = 3;
int speed_y = 3;
std::vector<BALL> balls;
std::vector<BALL>::iterator iter_balls;

std::vector<THREADS> threads;
THREADS KillerThread;
std::vector<THREADS>::iterator iter_threads;


void Move(int idx) {
	
	balls[idx].x += balls[idx].speed_X;
	balls[idx].y += balls[idx].speed_Y;

	if (balls[idx].x - circle_size / 2 < RectView.left)
	{
		balls[idx].speed_X *= -1;
		balls[idx].x = RectView.left + circle_size / 2;
	}
	else if (balls[idx].x + circle_size / 2 > RectView.right)
	{
		balls[idx].speed_X *= -1;
		balls[idx].x = RectView.right - circle_size / 2;
	}

	if (balls[idx].y - circle_size / 2 < RectView.top)
	{
		balls[idx].speed_Y *= -1;
		balls[idx].y = RectView.top + circle_size / 2;
	}
	else if (balls[idx].y + circle_size / 2 > RectView.bottom)
	{
		balls[idx].speed_Y *= -1;
		balls[idx].y = RectView.bottom - circle_size / 2;
	}
}

void isCollide(int idx)
{
	if (balls.size() > 1)
	{
		for (int i = 0; i < balls.size() - 1; i++)
		{
			for (int j = i + 1; j < balls.size(); j++)
			{
				double dist = pow(pow((balls[j].x - balls[i].x), 2) + pow((balls[j].y - balls[i].y), 2), 0.5);
				if (dist <= circle_size)
				{
					balls[i].isCollide = true;
					balls[j].isCollide = true;
				}
			}
		}
	}

	for (int i = 0; i < balls.size(); i++)
		if (balls[i].isCollide)
		{
			balls[i].isAlive = false;
			threads[i].isAlive = false;
		}

}

void Thread_Proc(void *arg)
{		

	int idx = *((int*)arg);

	
	while (1)
	{

		if (threads[idx].isAlive)
		{
			EnterCriticalSection(&crit);

			if (balls[idx].isAlive)
			{

				Move(idx);
				isCollide(idx);
			}
			else
				threads[idx].isAlive = false;
			LeaveCriticalSection(&crit);
		}
		else
			return;

		Sleep(300);

	}
}


void KillerThread_Proc()
{
	if (!KillerThread.isAlive)
	{
		return;
	}
	else if (threads.size() >= 1)
	{
		while (1)
		{
			EnterCriticalSection(&crit);
			/*for (iter_threads = threads.begin(); iter_threads < threads.end(); iter_threads++)
			{
				if (!iter_threads->isAlive)
				{
					CloseHandle(threads[iter_threads->id].handle);
					threads.erase(iter_threads);
					iter_threads--;
				}
			}*/

			for (iter_balls = balls.begin(); iter_balls < balls.end(); iter_balls++)
			{

				if (!balls[i].isAlive && !threads[i].isAlive)
				{

					balls.erase(iter_balls + balls[i].id);
					threads.erase(iter_threads + i);

				}
				else if (!balls[i].isAlive &&  threads[i].isAlive)
				{
					threads[balls[i].id].isAlive = false;
					balls.erase(iter_balls + balls[i].id);
					threads.erase(iter_threads + i);
				}
				else if (balls[i].isAlive && !threads[i].isAlive)
				{
					balls[i].isAlive = false;
				}
			}

			Sleep(1000);
		}
	}
}

void DrawBalls(HDC hdc)
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
	FillRect(BackMemDC, &RectView, (HBRUSH)GetStockObject(WHITE_BRUSH));


	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i].isAlive)
		{
			balls[i].rrr = balls[i].x % 256;
			balls[i].ggg = (balls[i].x + balls[i].y) % 256;
			balls[i].bbb = balls[i].y % 256;

			HBRUSH MyBrush = CreateSolidBrush(RGB(balls[i].rrr, balls[i].ggg, balls[i].bbb));
			SelectObject(BackMemDC, MyBrush);
			Ellipse(BackMemDC, balls[i].x - circle_size / 2, balls[i].y - circle_size / 2, balls[i].x + circle_size / 2, balls[i].y + circle_size / 2);
			DeleteObject(MyBrush);
		}
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
	{
		GetClientRect(hWnd, &RectView);
		InitializeCriticalSection(&crit);
		SetTimer(hWnd, 1, 13, &TimerProc);
		KillerThread.id = 0;
		KillerThread.isAlive = true;
		KillerThread.handle = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))KillerThread_Proc, NULL, 0, NULL);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (balls.size() == 0)
		{
			BALL tmp;
			tmp.id = 0;
			tmp.x = rand() % RectView.right;
			tmp.y = rand() % RectView.bottom;
			tmp.rrr = tmp.x % 256;
			tmp.ggg = (tmp.x + tmp.y) % 256;
			tmp.bbb = tmp.y % 256;
			tmp.speed_X = rand() % 5 + 4;
			tmp.speed_Y = rand() % 5 + 4;

			tmp.isAlive = true;
			tmp.isCollide = false;
			balls.push_back(tmp);

			THREADS tmp_thread;
			tmp_thread.id = tmp.id;
			tmp_thread.isAlive = true;
			tmp_thread.handle = NULL;
			threads.push_back(tmp_thread);
			threads[tmp.id].handle = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))Thread_Proc, (void *)&tmp_thread.id, 0, NULL);

		}
		else
		{

			BALL tmp;
			tmp.id = balls.size();
			tmp.x = rand() % RectView.right;
			tmp.y = rand() % RectView.bottom;
			tmp.rrr = tmp.x % 256;
			tmp.ggg = (tmp.x + tmp.y) % 256;
			tmp.bbb = tmp.y % 256;
			tmp.speed_X = rand() % 5 + 4;
			tmp.speed_Y = rand() % 5 + 4;

			tmp.isAlive = true;
			tmp.isCollide = false;
			balls.push_back(tmp);

			THREADS tmp_thread;
			tmp_thread.id = tmp.id;
			tmp_thread.handle = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))Thread_Proc, (void *)&tmp_thread.id, 0, NULL);
			tmp_thread.isAlive = true;

			threads.push_back(tmp_thread);
			break;
		}

		iter_balls = balls.begin();
		iter_threads = threads.begin();
		LeaveCriticalSection(&crit);
	}
	break;
	case WM_PAINT:
	{
		EnterCriticalSection(&crit);

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TCHAR status[100];
		wsprintf(status, _T("생성된 공 : %d개 / 생성된 쓰레드 : %d개"), balls.size(), threads.size());
		DrawBalls(hdc);
		TextOut(hdc, 10, 10, status, lstrlen(status));
		EndPaint(hWnd, &ps);

		LeaveCriticalSection(&crit);
	}
	break;
	case WM_GETMINMAXINFO:
		GetClientRect(hWnd, &RectView);
		return 0;
	case WM_DESTROY:
		KillerThread.isAlive = false;
		Sleep(100);
		while (KillerThread.isAlive)
		{
			EnterCriticalSection(&crit);

			CloseHandle(KillerThread.handle);

			LeaveCriticalSection(&crit);
		}
		KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
