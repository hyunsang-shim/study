// netOmok_Client.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "netOmok_Client.h"
#include <vector>
//
//
// for Windows Socket Programming
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "msimg32.lib")



#define MAX_LOADSTRING 100
#define WM_ASYNC WM_USER + 2
#define BOARD_SIZE 500
#define CHAT_WINDOW_WIDTH 500


//  �޽��� ����ü
typedef struct OMOK_MSG {
	bool turn;
	POINT newStone;
}OMOK_MSG;



// ���� ����:
HINSTANCE				hInst;                          // ���� �ν��Ͻ��Դϴ�.
WCHAR					szTitle[MAX_LOADSTRING];        // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR					szWindowClass[MAX_LOADSTRING];  // �⺻ â Ŭ���� �̸��Դϴ�.
OMOK_MSG					MyMessage;						// �޽��� ���ۿ� ����ü
std::vector<POINT>		MyStones, OpponentStones;		// �ٵ� �� ��ǥ ���� ����� ����
RECT					RectClient;						// ȭ�� �׸���� Ŭ���̾�Ʈ ����



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
    LoadStringW(hInstance, IDC_NETOMOK_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NETOMOK_CLIENT));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NETOMOK_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, NULL, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
	char				sendmessage[200];
	static TCHAR		MyMsg[200];
	static TCHAR		NotMyMsg[200];
	static int			count = 0;
	int					tmpLen, MyMsgLen, NotMyMsgLen;
	char				buffer[200];
	static int			msgLines = 0;
	static int			mouseX, mouseY;
	static POINT		laststone;
	static int			MyTurnNumber = -1;

    switch (message)
    {
	case WM_CREATE:
		SetRect(&RectClient, 0, 0, BOARD_SIZE + CHAT_WINDOW_WIDTH + (GetSystemMetrics(SM_CXFRAME) >> 1), BOARD_SIZE + (GetSystemMetrics(SM_CYFRAME) << 1) + GetSystemMetrics(SM_CYCAPTION));
		AdjustWindowRect(&RectClient, WS_OVERLAPPEDWINDOW, FALSE);
		MoveWindow(hWnd,
			GetSystemMetrics(SM_CXSCREEN) / 2 - BOARD_SIZE + CHAT_WINDOW_WIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - BOARD_SIZE / 2,
			200, 150, TRUE);

		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_READ);
		if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) != -1)
		{
			MessageBox(NULL, _T("Connection Failed!"), _T("Error!!"), MB_OK);
			PostQuitMessage(0);
		}
		
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_READ:

			tmpLen = recv(s, buffer, 200, 0);
			buffer[tmpLen] = NULL;
#ifdef _UNICODE
			if (MyTurnNumber == buffer[0] - 48)
			{
				MyMsgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);		
				MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), MyMsg, MyMsgLen);
				MyMsg[MyMsgLen] = NULL;
			}
			else
			{
				NotMyMsgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
				MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NotMyMsg, NotMyMsgLen);
				NotMyMsg[NotMyMsgLen] = NULL;
			}
#else
			if (MyTurnNumber == buffer[0] - 48)
				strcpy_s(MyMsg, buffer);
			else
				strcpy_s(NotMyMsg, buffer);
#endif
		
			/*
			���� �޽����� �ؼ��ؼ� �̹��� �׸� ��ǥ�� ã�´�.
			*/
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		default:
			break;
		}
		break;
	case WM_MOUSEMOVE:	
		break;	  
	case WM_LBUTTONDOWN:
		sprintf(sendmessage, "%d : %d %d", MyTurnNumber, LOWORD(lParam), HIWORD(lParam));
		send(s, sendmessage, strlen(sendmessage)+1, 0);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			/*
			�ٵ����� �׸���.
			���� �׸���.
			*/
			TextOut(hdc, 10, 10, MyMsg, lstrlen(MyMsg));
			TextOut(hdc, 10, 30, NotMyMsg, lstrlen(NotMyMsg));
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


