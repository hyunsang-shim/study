// Win32_Server.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "netOmok_Server.h"
#include <stdio.h>
#include <vector>
#include <string>


//
//
// for Windows Socket Programming
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
int WinSockTest_Server();
//>>
#define MAX_LOADSTRING 100
#define WM_ASYNC WM_USER + 2

//  �޽��� ����ü
typedef struct omok_message {
	int turn;
	POINT newStone;
}OMOK_MSG;

// ���� ����:
HINSTANCE			hInst;                           // ���� �ν��Ͻ��Դϴ�.
WCHAR				szTitle[MAX_LOADSTRING];         // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR				szWindowClass[MAX_LOADSTRING];   // �⺻ â Ŭ���� �̸��Դϴ�.
OMOK_MSG			MyMessage;						 // �޽��� ���ۿ� ����ü
						
RECT RectClient;



// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//
	// just check that connected or not
	//return WinSockTest_Server();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_NETOMOK_SERVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NETOMOK_SERVER));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NETOMOK_SERVER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_NETOMOK_SERVER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
#define MSG_MAX_LENGTH 200

	static WSADATA		wsadata;
	static SOCKET		s, last;
	static std::vector<SOCKET> cs;
	static int			cnt_connection = 0;
	static int			found = -1;
	static TCHAR		msg[MSG_MAX_LENGTH];
	static SOCKADDR_IN	addr = { 0 }, c_addr;
	int					size, msgLen;
	char				buffer[MSG_MAX_LENGTH];
	char				sendmessage[MSG_MAX_LENGTH];

	switch (message)
	{
	case WM_CREATE:
		MoveWindow(hWnd, 0, 0, 800, 200, TRUE);
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		//
		// check Binding
		if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)))
		{
			MessageBox(NULL, _T("Binding Failed!"), _T("Error"), MB_OK);
			return 0;
		}
		else
		{
			MessageBox(NULL, _T("Binding Successful!"), _T("Success"), MB_OK);
		}


		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT | FD_CLOSE);
		//
		// Check Listening
		if (listen(s, 5) == SOCKET_ERROR)
		{
			MessageBox(NULL, _T("Listening Failed!"), _T("Error"), MB_OK);
			return 0;
		}
		else
		{
			MessageBox(NULL, _T("Listening Successful!"), _T("Success"), MB_OK);
		}
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
			size = sizeof(c_addr);
			// ���� �õ��� ���� ������ ������ �޴´�. 2��° ���ĺ��ʹ� ������ �ź��Ѵ�.
			if (cs.size() < 2)
			{
				cs.push_back(accept(s, (LPSOCKADDR)&c_addr, &size));
				WSAAsyncSelect(cs[cs.size() - 1], hWnd, WM_ASYNC, FD_READ | FD_CLOSE);

				sprintf(sendmessage, "$ID$%d", cs.size()-1);
				send(cs[cs.size() - 1], sendmessage, strlen(sendmessage) + 1, 0);
			}
			else
			{
				SOCKET tmp = accept(s, (LPSOCKADDR)&c_addr, &size);
				WSAAsyncSelect(tmp, hWnd, WM_ASYNC, FD_READ | FD_CLOSE);

				sprintf(sendmessage, "$QUIT$���̻� ������ �� �����ϴ�.");
				send(tmp, sendmessage, strlen(sendmessage) + 1, 0);
			}
			break;
		case FD_READ:
		{
			memset(msg, 0, MSG_MAX_LENGTH);
			SOCKET tmp = wParam;
			msgLen = recv(tmp, buffer, MSG_MAX_LENGTH, 0);


			buffer[msgLen] = NULL;
#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msgLen);

			if (msgLen < MSG_MAX_LENGTH - 1)
			{
				TCHAR tcharTmp[MSG_MAX_LENGTH];
				wsprintf(tcharTmp, _T("%s"), msg);
				sprintf(sendmessage, "%s", buffer);
				wsprintf(msg, _T("%s"), tcharTmp);
			}
#else		
			strcpy_s(msg, buffer);
#endif			
				send(cs[0], sendmessage, strlen(sendmessage) + 1, 0);
				send(cs[1], sendmessage, strlen(sendmessage) + 1, 0);		

			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
		case FD_CLOSE:
		{
			if (cs[0] == wParam)
			{
				cs[0] = { NULL };
				memset(sendmessage, 0, sizeof(sendmessage));
				sprintf(sendmessage, "0%s", "������ ������ �����߽��ϴ�.");
				send(cs[0], sendmessage, strlen(sendmessage) + 1, 0);
			}
			else if (cs[1] == wParam)
			{
				cs[1] = { NULL };
				memset(sendmessage, 0, sizeof(sendmessage));
				sprintf(sendmessage, "1%s", "������ ������ �����߽��ϴ�.");
				send(cs[1], sendmessage, strlen(sendmessage) + 1, 0);
			}
		}
			break;
		default:
			break;
		}
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, _T("�ƹ� Ű�� ��������."), lstrlen(_T("�ƹ� Ű�� ��������.")));
		TextOut(hdc, 10, 30, msg, (int)lstrlen(msg));
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}




int WinSockTest_Server()
{
	TCHAR			message[300];
	WSADATA			wsadata;
	SOCKET			s;
	SOCKADDR_IN		addr = { 0 };


	TCHAR Title[128];
	wsprintf(Title, _T("���� �˸�"));

	do {
		SOCKADDR_IN	c_addr;
		char		buffer[100];

#ifdef _UNICODE
		TCHAR wbuffer[100];
#endif	// _UNICODE
		int			msgLen;
		int			size = sizeof(c_addr);
		SOCKET		cs = accept(s, (LPSOCKADDR)&c_addr, &size);
		msgLen = recv(cs, buffer, 100, 0);
		buffer[msgLen] = NULL;

#ifdef _UNICODE
		msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), wbuffer, msgLen);
		wbuffer[msgLen] = NULL;
		wsprintf(message, _T("[Ŭ���̾�Ʈ] ���� �� : \n%s\n\nŬ���̾�Ʈ ������ Ȯ�� �߽��ϴ�.\n������ �����Ͻðڽ��ϱ�?"), wbuffer);
#else
		wsprintf(message, _T("[Ŭ���̾�Ʈ] ���� �� : \n%s\n\nŬ���̾�Ʈ ������ Ȯ�� �߽��ϴ�.\n������ �����Ͻðڽ��ϱ�?"), buffer);
#endif // _UNICODE
	} while (MessageBox(NULL, message, Title, MB_YESNO) == IDNO);


	return 1;
}
