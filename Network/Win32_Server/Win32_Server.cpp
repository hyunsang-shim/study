// Win32_Server.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Win32_Server.h"
#include <stdio.h>
#include <vector>


//
//
// for Windows Socket Programming
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
int WinSockTest_Server();
//>>
#define MAX_LOADSTRING 100
#define WM_ASYNC WM_USER + 2

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.


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
    LoadStringW(hInstance, IDC_WIN32_SERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32_SERVER));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32_SERVER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32_SERVER);
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
	static WSADATA		wsadata;
	static SOCKET		s;
	static std::vector<SOCKET> cs;
	static int			cnt_connection = 0;
	static TCHAR		msg[200];
	static SOCKADDR_IN	addr = { 0 }, c_addr;
	int					size, msgLen;
	char				buffer[200];
	char				sendmessage[200];

    switch (message)
    {
	case WM_CREATE:
		MoveWindow(hWnd, 0,0, 800, 200,	TRUE);
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


		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);
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
			if (cnt_connection == 0)
			{
				cs.push_back(accept(s, (LPSOCKADDR)&c_addr, &size));				
				WSAAsyncSelect(cs.at(cnt_connection), hWnd, WM_ASYNC, FD_READ);
			}
			else
			{
				SOCKET tmp;
				tmp = accept(s, (LPSOCKADDR)&c_addr, &size);
				for (int i = 0; i < cs.size(); i++)
				{
					if (tmp == cs.at(i))
						WSAAsyncSelect(cs.at(i), hWnd, WM_ASYNC, FD_READ);
				}
				
				WSAAsyncSelect(cs.at(cnt_connection), hWnd, WM_ASYNC, FD_READ);
			}
			break;

			cnt_connection = cs.size();
		case FD_READ:
			msgLen = recv(cs.at(cnt_connection), buffer, 100, 0);
			buffer[msgLen] = NULL;
#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msgLen);
			msg[msgLen] = NULL;
#else
			strcpy_s(msg, buffer);
#endif

			for (int i = 0; i < cs.size(); i++)
			{				
				send(cs.at(i), buffer, strlen(buffer) + 1, 0);
			}

			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		case FD_CLOSE:

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
			TextOut(hdc, 10, 50, msg, (int)_tcslen(msg));
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		if (cs.empty())
			break;
		else
		{
			for (int i = 0; i < cs.size(); i++)
			{
				sprintf(sendmessage, "%s%d%s", "�����Ǣֱñȿ��ٴ絵�� ������ȯ���Ͽ��ٳ��ټ�����", i, "�̿���.");
				send(cs.at(i), sendmessage, strlen(sendmessage) + 1, 0);
			}
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
