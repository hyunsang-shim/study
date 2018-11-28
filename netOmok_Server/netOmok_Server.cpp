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
//>>


#define MAX_LOADSTRING 100
#define MSG_MAX_LENGTH 200
#define WM_ASYNC WM_USER + 2

#define GAME 1234
#define SYSTEM_OPPONENT_QUIT 1000
#define SYSTEM_CANNOT_JOIN 9999
#define SYSTEM_KEEP_ALIVE 7777
#define SYSTEM_NEW_ID 2000
#define SYSTEM_INVALID_ACTION 6666
#define SYSTEM_PROHIBITED 3333



//  �޽��� ����ü
// int MsgType;
// int ThisTurn;
// int NewStoneX;
// int NewStoneY;
// short StoneColor;
// int NextTurn;
// int GameState;
typedef struct omok_message {
	int MsgType;
	int ThisTurn;
	int NewStoneX;
	int NewStoneY;
	short StoneColor;
	int NextTurn;
	int GameState;
}OMOK_MSG;

typedef struct omok_system_msg {
	int MsgType;
	char MSG1[80];
	char MSG2[80];
}OMOK_MSG_SYS;

// ���� ����:
HINSTANCE			hInst;                           // ���� �ν��Ͻ��Դϴ�.
WCHAR				szTitle[MAX_LOADSTRING];         // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR				szWindowClass[MAX_LOADSTRING];   // �⺻ â Ŭ���� �̸��Դϴ�.
static OMOK_MSG		GameMessage, Recieved;		// ���� ���� �޽��� ����/���ſ� ����ü
static OMOK_MSG_SYS	SystemMessage;				// �ý��� �޽��� ����.���ſ� ����ü

char				Board[19][19] = { 0 };

RECT RectClient;



// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
int					checkProhibitions(int x, int y);

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

	static WSADATA		wsadata;					// WSADATA ����ü
	static SOCKET		s;							// ������ ���� ����ü
	static std::vector<SOCKET> cs;					// Ŭ���̾�Ʈ ���� ���� ����(vector)		
	static SOCKADDR_IN	addr = { 0 }, c_addr;		// ���� �ּ�. 
	int					size, MsgLen;				// ���� ������, �����ּ� ũ�� ���� �����ϱ� ���� ����
	char				buffer[MSG_MAX_LENGTH];		// ���� �޽����� �Խ� �����ϴ� ����	
	static int			LastTurn = -1;				// ���������� ������ �÷��̾�.
	static int			CurrentPlayer;				// ���������� ���� �� ������ Socket ID
	static int			NextPlayer;					// ���� ������ �÷��̾�
	static bool			GameState = false;					// ���� ���� ����
	static HANDLE		hFile = CreateFile(_T("server.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
	static char			Filename[32];
	DWORD				fReadResult;
	static TCHAR		ServerStatus[80];			// ���� ���� ǥ��


	switch (message)
	{
	case WM_CREATE:
		MoveWindow(hWnd, 0, 0, 800, 200, TRUE);
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		
		if (ReadFile(hFile, Filename, sizeof(Filename), &fReadResult, NULL))
		{
			Filename[strlen(Filename)] = NULL;
			addr.sin_addr.S_un.S_addr = inet_addr(Filename);
			memset(ServerStatus, 0, sizeof(ServerStatus));

			TCHAR tmpStr[80];
			int tmplen = MultiByteToWideChar(CP_ACP, 0, Filename, strlen(Filename), NULL, NULL);
			MultiByteToWideChar(CP_ACP, 0, Filename, strlen(Filename), tmpStr, tmplen);
			tmpStr[tmplen] = NULL;

			wsprintf(ServerStatus, _T("%s %s"), _T("���� IP : "), tmpStr);
			ServerStatus[lstrlen(ServerStatus)] = '\0';
		}
		else
		{
			addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
			memset(ServerStatus, 0, sizeof(ServerStatus));
			wsprintf(ServerStatus, _T("%s"), _T("���� IP : 127.0.0.1"));
			ServerStatus[lstrlen(ServerStatus)] = '\0';
			
		}
		//
		// check Binding
		if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)))
		{
			MessageBox(NULL, _T("Binding Failed!"), _T("Error"), MB_OK);
			return 0;
		}

		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT | FD_CLOSE);
		//
		// Check Listening
		if (listen(s, 5) == SOCKET_ERROR)
		{
			MessageBox(NULL, _T("Listening Failed!"), _T("Error"), MB_OK);
			return 0;
		}
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
		{
			size = sizeof(c_addr);
			// ���� �õ��� ���� ������ ������ �޴´�. 2��° ���ĺ��ʹ� ������ �ź��Ѵ�.

			//
			// 2��° �÷��̾ �������� ���� ������ ���� ���� ������ �Ѱ��ش�.
			if (cs.size() == 1)
			{

				// 2��° ������ �ٷ� ���� ���� �ִ´�.
				cs.push_back(accept(s, (LPSOCKADDR)&c_addr, &size));
				WSAAsyncSelect(cs[cs.size() - 1], hWnd, WM_ASYNC, FD_READ | FD_CLOSE);

				// ù��° ���� �������� ���� �޽��� ����
				GameMessage.MsgType = GAME;
				GameMessage.NewStoneX = -1;
				GameMessage.NewStoneY = -1;
				GameMessage.ThisTurn = cs[0];
				GameMessage.NextTurn = cs[1];
				GameMessage.StoneColor = 1;
				GameMessage.GameState = 1;
				CurrentPlayer = cs[0];
				send(cs[0], (char*)&GameMessage, sizeof(GameMessage) + 1, 0);


				
				// �ι�° ���� �������� ���� �޽��� ����
				GameMessage.ThisTurn = cs[0];
				GameMessage.NextTurn = cs[1];
				GameMessage.StoneColor = -1;				
				NextPlayer = cs[1];
				send(cs[1], (char*)&GameMessage, sizeof(GameMessage) + 1, 0);

				GameState = true;
			}
			//�����ڰ� ������ �޾Ƶ��δ�.
			else if (cs.size() == 0)
			{
				cs.push_back(accept(s, (LPSOCKADDR)&c_addr, &size));
				WSAAsyncSelect(cs[cs.size() - 1], hWnd, WM_ASYNC, FD_READ | FD_CLOSE);
				SystemMessage.MsgType = SYSTEM_NEW_ID;
				sprintf(SystemMessage.MSG1, "%d", cs[cs.size() - 1]);
				
				if (cs.size() == 1)
					sprintf(SystemMessage.MSG2, "%d", 1);
				else
					sprintf(SystemMessage.MSG2, "%d", -1);


				send(cs[cs.size() - 1], (char*)&SystemMessage, sizeof(SystemMessage) + 1, 0);

			}
			else
			{
				SOCKET tmp = accept(s, (LPSOCKADDR)&c_addr, &size);
				WSAAsyncSelect(tmp, hWnd, WM_ASYNC, FD_READ | FD_CLOSE);
				SystemMessage.MsgType = SYSTEM_CANNOT_JOIN;
				sprintf_s(SystemMessage.MSG1, "���� ����");
				sprintf_s(SystemMessage.MSG2, "�ο� �ʰ��� ���忡 �����Ͽ����ϴ�.\n������ �����մϴ�.");
				send(tmp, (char*)&SystemMessage, sizeof(SystemMessage), 0);
			}
		}
		InvalidateRgn(hWnd, NULL, TRUE);
			break;
		case FD_READ:
		{
			memset(buffer, 0, 200);
			MsgLen = recv(CurrentPlayer, buffer, 200, 0);
			buffer[MsgLen] = NULL;
			OMOK_MSG_SYS* tmpsys = (OMOK_MSG_SYS*)buffer;
			
			switch (tmpsys->MsgType)
			{
			case GAME:
				//���� �޽����� ����
				OMOK_MSG* tmp = (OMOK_MSG*)buffer;
				Recieved.ThisTurn = tmp->ThisTurn;			// ��� ���� �� ����
				Recieved.NewStoneX = tmp->NewStoneX;		// ��� ���� �� ������ �� ��ġ column ��
				Recieved.NewStoneY = tmp->NewStoneY;		// ��� ���� �� ������ �� ��ġ row ��
				Recieved.StoneColor = tmp->StoneColor;		// ��� ���� �� ������ �� ����
				Recieved.NextTurn = tmp->NextTurn;			// ���� �� ���� (����)


				// ������ �� ���� ����
				// �̹� �Ͽ� �ؾ� �ϴ� ������ �´ٸ� OK
				// �ƴϸ� ERROR (���ư�!)
				if (Recieved.ThisTurn == CurrentPlayer)
				{
					CurrentPlayer = NextPlayer;
					NextPlayer = Recieved.ThisTurn;
				}
				else
				{
					SystemMessage.MsgType = SYSTEM_INVALID_ACTION;
				}

				// �ٵ��� ���� ������Ʈ
				// �ֵ� �ɱ�?
				if (checkProhibitions(Recieved.NewStoneX, Recieved.NewStoneY))
				{
					Board[Recieved.NewStoneY][Recieved.NewStoneX] = Recieved.StoneColor;
					GameMessage.MsgType = GAME;
					GameMessage.NewStoneX = Recieved.NewStoneX;
					GameMessage.NewStoneY = Recieved.NewStoneY;
					GameMessage.NextTurn = NextPlayer;
					GameMessage.ThisTurn = CurrentPlayer;
					GameMessage.StoneColor = Recieved.StoneColor;

					for (int i = 0; i < cs.size(); i++)
					{
						send(cs[i], (char*)&GameMessage, sizeof(GameMessage), 0);
					}
				}
				else
				{
					SystemMessage.MsgType = SYSTEM_INVALID_ACTION;
					sprintf(SystemMessage.MSG1, "�߸��� �����Դϴ�.");
					sprintf(SystemMessage.MSG2, "�� ������ �� �� �����ϴ�.");
					
					
				}

				// ������Ʈ �� ������ �غ�
				
				
				
				break;
			}

			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
		case FD_CLOSE:
		{
			std::vector<SOCKET>::iterator iter;
			
				for (iter = cs.begin(); iter != cs.end(); )
				{
					if(*iter == (SOCKET)wParam)
					{
						iter = cs.erase(iter);
						break;
					}
					else
					{
						iter++;
					}
				}

				if (!cs.empty())
				{
					for (int i = 0; i < cs.size(); i++)
					{
						if (cs[i] != wParam)
						{
							//���� �޽���
						}
					}
				}
		}
			break;
		default:
			break;
		}		
		break;	
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);		
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
		TextOut(hdc, 10, 10, ServerStatus, lstrlen(ServerStatus));
		TCHAR p1[32];
		TCHAR p2[32];
		if (cs.empty())
		{
			memset(p1, 0, 32);
			memset(p2, 0, 32);
			wsprintf(p1, _T("%s"), _T("����(��) : ���� �����"), 0);
			wsprintf(p2, _T("%s"), _T("�İ�(��) : ���� �����"), 0);
		}
		else if (cs.size() == 1)
		{
			memset(p1, 0, 32);
			memset(p2, 0, 32);
			wsprintf(p1, _T("%s%d"), _T("����(��) : "), cs[0]);
			wsprintf(p2, _T("%s"), _T("�İ�(��) : ���� �����"), 0);
		}
		else if (cs.size() == 2)
		{
			memset(p1, 0, 32);
			memset(p2, 0, 32);
			wsprintf(p1, _T("%s%d"), _T("����(��) : "), cs[0]);
			wsprintf(p2, _T("%s%d"), _T("�İ�(��) : "), cs[1]);
		}
		TextOut(hdc, 10, 30, p1, lstrlen(p1));
		TextOut(hdc, 10, 50, p2, lstrlen(p2));
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

int checkProhibitions(int x, int y)
{
	char tmp[19][19];
	int cnt_open3;
	int cnt_open4;

	for (int row = 0; row < 19; row++)
		for (int col = 0; col < 19; col++)
			tmp[row][col] = Board[row][col];

	tmp[y][x] = Recieved.StoneColor;

	//�¸� �˻�. 5���� �������̸� �¸�
	for (int row = 0; row < 19; row++)
		for (int col = 0; col < 19; col++)
		{
			if (tmp[row][col] == 0)
				break;
			else
			{
				for (int i = row; i < 19-row; i++)
				{
					//������


				}
			}

		}

	return true;
}
