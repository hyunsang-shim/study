// Client.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//
#define _WINDOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include "Client.h"

// Server Addresses
// should activated just one.
//#define SERVER_ADDR "165.246.163.66"	
#define SERVER_ADDR "165.246.163.71"	// Shim, Hyunsang
#define BUFFER_SIZE 157
#define BUFFER_SIZE2 314
#define WM_ASYNC (WM_USER + 2)
#define MAX_LOADSTRING 100

using namespace std;

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND g_hWnd;
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
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = nullptr;
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
	static WSADATA		wsadata;
	static SOCKET		s;
	static SOCKADDR_IN	addr = { 0 };
	static char			buffer[BUFFER_SIZE];
	static TCHAR		rMsg[BUFFER_SIZE2];
	static TCHAR		sMsg[BUFFER_SIZE];
	static int			count;
	int					msgLen;


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
		// inet_addr is deprecated and recommanded to #include <WS2tcpip.h> and use inet_pton()
		// or include #define _WINDOCK_DEPRECATED_NO_WARNINGS before all the includes		
		addr.sin_addr.S_un.S_addr = inet_addr(SERVER_ADDR);


		//
		// WSAAsyncSelect is deprecated API and recommended to use WSAEventSelect() instead
		// but at this moment, to follow the textbook, use WSAAsyncSelect()
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_READ | FD_CLOSE);


		if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) != -1)
		{
			MessageBox(hWnd, "Connection Error ", "Error", MB_OK);
			return 0;
		}
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_READ:
			msgLen = recv(s, buffer, BUFFER_SIZE, 0);
			buffer[msgLen] = NULL;
#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msgLen);
			msg[msgLen] = NULL;
#else
			strcpy_s(rMsg, BUFFER_SIZE, buffer);
#endif			
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		if (wParam == VK_RETURN)
			if (s == INVALID_SOCKET)
				return 0;
			else
			{
#ifdef _UNICODE
				msgLen = wideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, sMsg, -1, buffer, msgLen, NULL, NULL);
#else
				strcpy_s(buffer, sMsg);
				msgLen = strlen(buffer);
#endif
				send(s, (LPSTR)buffer, msgLen + 1, 0);
				count = 0;
				return 0;
			}
		sMsg[count++] = wParam;
		sMsg[count] = NULL;
		return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			if (_tcscmp(rMsg, _T("")))
				TextOut(hdc, 0, 30, rMsg, (int)_tcslen(rMsg));
			TextOut(hdc, 0, 0, sMsg, (int)_tcslen(sMsg));
            EndPaint(hWnd, &ps);
        }
        break;
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
