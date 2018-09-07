// MUltiThread_study01.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MUltiThread_study01.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE			hInst;							// 현재 인스턴스입니다.
WCHAR				szTitle[MAX_LOADSTRING];		// 제목 표시줄 텍스트입니다.
WCHAR				szWindowClass[MAX_LOADSTRING];	// 기본 창 클래스 이름입니다.
HWND				hWnd;							// WinMain() 함수의 지역 변수를 전역 변수화	


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
    LoadStringW(hInstance, IDC_MULTITHREADSTUDY01, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MULTITHREADSTUDY01));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MULTITHREADSTUDY01));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MULTITHREADSTUDY01);
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

   // 전역변수화 했으므로 앞에 자료형을 쓸 필요가 없음.
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


//
// 함수 : ThreadProc()
//
// 목적 : 쓰레드 처리를 한다.
//
//
HANDLE hEvent;
int max;
void ThreadProc(void *arg)
{
	HDC hdc;
	int i;
	int xPos = *((int*)arg);
	srand((unsigned)time(0));
	hdc = GetDC(hWnd);
	SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));

	for (i = 0; i < 10; i++)
	{
		int num;
		WaitForSingleObject(hEvent, INFINITE);
		num = rand() % 500;
		TCHAR tmp[3];
		wsprintf(tmp, _T("%d"), i);
		TextOut(hdc, i * 20, 10, tmp, lstrlen(tmp));

		if (num > max)
		{
			Sleep(600);
			max = num;		
			Rectangle(hdc, i*20+xPos, 0, i * 20 +xPos + 20, num);
		}
		SetEvent(hEvent);
	}
	ReleaseDC(hWnd, hdc);
	return;
}

#define THREAD_NUM 10

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
	static HANDLE hThread[THREAD_NUM];
	static int xPos[THREAD_NUM];
	int i;
	std::vector<RECT>  aa;
	
	switch (message)
	{	
	case WM_CREATE:
		for (i = 0; i< THREAD_NUM; i++)
			xPos[i] = i * 100;
		max = 0;
		break;
	case WM_LBUTTONDOWN:
		hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
		for (i = 0; i < THREAD_NUM; i++);
		{
			hThread[i] = (HANDLE)_beginthreadex(
				NULL, 
				0, 
				(unsigned int(__stdcall *)(void *))ThreadProc,
				(void *)&xPos[i],
				0, 
				NULL);
			Sleep(600);
		}
		WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);
			CloseHandle(hEvent);
		break;
	case WM_DESTROY:
		for (i = 0; i < THREAD_NUM; i++)
			CloseHandle(hThread[i]);
		PostQuitMessage(0);
		return 0;
	}

    return DefWindowProc(hWnd, message, wParam, lParam);
}
