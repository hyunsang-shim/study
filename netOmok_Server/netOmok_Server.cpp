// Win32_Server.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
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

//  메시지 구조체
typedef struct omok_message {
	int turn;
	POINT newStone;
}OMOK_MSG;

// 전역 변수:
HINSTANCE			hInst;                           // 현재 인스턴스입니다.
WCHAR				szTitle[MAX_LOADSTRING];         // 제목 표시줄 텍스트입니다.
WCHAR				szWindowClass[MAX_LOADSTRING];   // 기본 창 클래스 이름입니다.
OMOK_MSG			MyMessage;						 // 메시지 전송용 구조체
						
RECT RectClient;



// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_NETOMOK_SERVER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NETOMOK_SERVER));

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

	return (int)msg.wParam;
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
			// 접속 시도가 있을 때마다 접속을 받는다. 2번째 이후부터는 접속을 거부한다.
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

				sprintf(sendmessage, "$QUIT$더이상 입장할 수 없습니다.");
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
				sprintf(sendmessage, "0%s", "상대방이 접속을 종료했습니다.");
				send(cs[0], sendmessage, strlen(sendmessage) + 1, 0);
			}
			else if (cs[1] == wParam)
			{
				cs[1] = { NULL };
				memset(sendmessage, 0, sizeof(sendmessage));
				sprintf(sendmessage, "1%s", "상대방이 접속을 종료했습니다.");
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
		// 메뉴 선택을 구문 분석합니다.
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
		TextOut(hdc, 10, 10, _T("아무 키나 누르세요."), lstrlen(_T("아무 키나 누르세요.")));
		TextOut(hdc, 10, 30, msg, (int)lstrlen(msg));
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

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

// 정보 대화 상자의 메시지 처리기입니다.
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
	wsprintf(Title, _T("서버 알림"));

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
		wsprintf(message, _T("[클라이언트] 님의 말 : \n%s\n\n클라이언트 접속을 확인 했습니다.\n서버를 종료하시겠습니까?"), wbuffer);
#else
		wsprintf(message, _T("[클라이언트] 님의 말 : \n%s\n\n클라이언트 접속을 확인 했습니다.\n서버를 종료하시겠습니까?"), buffer);
#endif // _UNICODE
	} while (MessageBox(NULL, message, Title, MB_YESNO) == IDNO);


	return 1;
}
