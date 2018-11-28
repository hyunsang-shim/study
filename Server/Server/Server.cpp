// Server.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#define _WINDOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"

// Server Addresses
// should activated just one.
//#define SERVER_ADDR "165.246.163.66"	
#define SERVER_ADDR "165.246.163.71"	// Shim, Hyunsang
#define BUFFER_SIZE 157
#define BUFFER_SIZE2 314
#define WM_ASYNC (WM_USER + 2)


using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;
vector<CharacterStatus_PC> g_vUsers;

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
    LoadStringW(hInstance, IDC_SERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SERVER));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SERVER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = nullptr;
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

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
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
	static WSADATA		wsadata;
	static SOCKET		s, cs;
	static char			buffer[BUFFER_SIZE];
	static TCHAR		rMsg[BUFFER_SIZE2];
	static TCHAR		sMsg[BUFFER_SIZE];
	static SOCKADDR_IN	addr = { 0 }, c_addr;
	static int			count;
	int					size, msgLen;

    switch (message)
    {   
	case WM_CREATE:
		if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		{
			MessageBox(hWnd, "Startup Error", "Error", MB_OK);
			return 0;
		}

		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s == INVALID_SOCKET)
		{
			MessageBox(hWnd, "Invalid Socket", "Error", MB_OK);
			return 0;
		}

		addr.sin_family = AF_INET;
		addr.sin_port = 20;

		//
		// inet_pton(AF_INET, SERVER_ADDR, &addr.sin_addr);	// inet_addr is deprecated and recommanded to #include <WS2tcpip.h> and use inet_pton()
		// or include #define _WINDOCK_DEPRECATED_NO_WARNINGS before all the includes
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		
		if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == -1)
		{
			MessageBox(hWnd, "Binding Error ", "Error", MB_OK);
			return 0;
		}

		//
		// WSAAsyncSelect is deprecated API and recommended to use WSAEventSelect() instead
		// but at this moment, to follow the textbook, use WSAAsyncSelect()
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);			
																

		if (listen(s, 5) == -1)
		{
			MessageBox(hWnd, "Listening Error ", "Error", MB_OK);
			return 0;
		}

		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
			size = sizeof(c_addr);
			cs = accept(s, (LPSOCKADDR)&c_addr, &size);
			WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_READ);
			break;
		case FD_READ:
			msgLen = recv(cs, buffer, BUFFER_SIZE, 0);
			buffer[msgLen] = NULL;

#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msgLen);
			msg[msgLen] = NULL;
#else
			strcpy_s(rMsg, BUFFER_SIZE, buffer);
#endif			
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: add something to draw using HDC.
			if (_tcscmp(rMsg, _T("")))
				TextOut(hdc, 0, 30, rMsg, (int)_tcslen(rMsg));
			TextOut(hdc, 0, 0, sMsg, (int)_tcslen(sMsg));
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CHAR:
		if (wParam == VK_RETURN)
			if (cs == INVALID_SOCKET)
				return 0;
			else
			{
#ifdef _UNICODE
				msgLen = WideCharToMultiByte(CP_ACP, 0, sMsg, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACA, 0, sStr);
#else
				strcpy_s(buffer, sMsg);
#endif
				send(cs, (LPSTR)buffer, strlen(buffer) + 1, 0);
				count = 0;
				return 0;				
			}
		sMsg[count++] = wParam;
		sMsg[count] = NULL;
		InvalidateRgn(hWnd, NULL, TRUE);
		return 0;		
    case WM_DESTROY:
		closesocket(s);
		WSACleanup();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
