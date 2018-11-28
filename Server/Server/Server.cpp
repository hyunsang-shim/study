// Server.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND g_hWnd;
vector<CharacterStatus_PC> g_vUsers;

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
    LoadStringW(hInstance, IDC_SERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SERVER));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SERVER));
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
