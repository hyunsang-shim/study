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
#define MSG_MAX_LENGTH 200
#define WM_ASYNC WM_USER + 2

#define BOARD_SIZE 500
#define BOARD_LINES 19
#define SQUARE_WIDTH 23
#define SQUARE_HEIGHT 25
#define BOARD_MARGIN_HEIGHT 25
#define BOARD_MARGIN_WIDTH 40


//  �޽��� ����ü
typedef struct OMOK_MSG {
	char SocketID[32];
	char NewStoneX[3];
	char NewStoneY[3];
	char ThisTurn[32];
}OMOK_MSG;



// ���� ����:
HINSTANCE				hInst;                          // ���� �ν��Ͻ��Դϴ�.
WCHAR					szTitle[MAX_LOADSTRING];        // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR					szWindowClass[MAX_LOADSTRING];  // �⺻ â Ŭ���� �̸��Դϴ�.
OMOK_MSG					MyMessage, RecievedMessage;						// �޽��� ����/���ſ� ����ü
std::vector<POINT>		MyStones, OpponentStones;		// �ٵ� �� ��ǥ ���� ����� ����
RECT					RectClient;						// ȭ�� �׸���� Ŭ���̾�Ʈ ����
char					Board[19][19] = { 0 };
//static int				flag = 1;						//�� ������ Ȯ���ϱ� ���� �ӽ� �簢��
int						MySocketID = -1;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void				DrawGameScene(HDC FrontDC);
void				DrawBoard(HDC BackMemDC);
void				DrawStones(HDC BackMemDC);
TCHAR*				ParseMessage(char message[]);


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
	//wcex.hbrBackground = (HBRUSH)(RGB(255,100,255));
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
	static SOCKET		s;	// ���� ����
	static SOCKADDR_IN	addr = { 0 };
	char				sendmessage[200];
	static TCHAR		MyMsg[200];
	static TCHAR		NotMyMsg[200];
	static std::string	resCommand;
	static int			count = 0;
	int					tmpLen, MyMsgLen, NotMyMsgLen;
	char				buffer[201];
	static int			msgLines = 0;
	static int			mouseX, mouseY;
	static POINT		laststone;
	static int			MyTurnNumber = -1;
	std::string			tmp;

    switch (message)
    {
	case WM_CREATE:
		SetRect(&RectClient, 0, 0, 500 + (GetSystemMetrics(SM_CXFRAME) << 1), 500 + (GetSystemMetrics(SM_CYFRAME) << 1) + GetSystemMetrics(SM_CYCAPTION));
		AdjustWindowRect(&RectClient, WS_OVERLAPPEDWINDOW, FALSE);
				
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_READ);
		if (connect(s, (LPSOCKADDR)&addr, sizeof(addr)) != -1)
		{
			MessageBox(NULL, _T("Connection Failed!"), _T("Error!!"), MB_OK);
		}
		
		break;	
	case WM_ASYNC:
		switch (lParam)
		{
			case FD_READ:
			{				
				memset(buffer, 0, 201);
				MyMsgLen = recv(s, buffer, 201, 0);
				buffer[MyMsgLen] = NULL;

				if (MySocketID == -1)
				{
					MySocketID = atoi(buffer);
				}			
				else
				{				
					strcpy_s(RecievedMessage.SocketID, 32, buffer);
					strcpy_s(RecievedMessage.NewStoneX, 3, buffer);
					strcpy_s(RecievedMessage.NewStoneY, 3, buffer);
					strcpy_s(RecievedMessage.ThisTurn, 32, buffer);
				}

		#ifdef _UNICODE
				MyMsgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
				MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), MyMsg, MyMsgLen);
				MyMsg[MyMsgLen] = NULL;
		#else
				strcpy_s(msg, buffer);
		#endif
				//Log.push_back(MyMsg);
				InvalidateRgn(hWnd, NULL, TRUE);
				break;
			default:
				break;
			}
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			
			DrawGameScene(hdc);
			TextOut(hdc, 550, 10, _T("My ID : "), lstrlen(_T("MY ID : ")));
			TCHAR tmp[32];
			wsprintf(tmp, _T("%d"), MySocketID);			
			TextOut(hdc, 600, 10, tmp, lstrlen(tmp));
			
			wsprintf(tmp, _T("This Turn : %s"), MyMessage.ThisTurn);
			TextOut(hdc, 550, 30, tmp, lstrlen(tmp));

			wsprintf(tmp, _T("SocketID : %s"), MyMessage.SocketID);
			TextOut(hdc, 550, 50, tmp, lstrlen(tmp));

			wsprintf(tmp, _T("Stone X : %s"), MyMessage.NewStoneX);
			TextOut(hdc, 550, 70, tmp, lstrlen(tmp));

			wsprintf(tmp, _T("Stone Y : %s"), MyMessage.NewStoneY);
			TextOut(hdc, 550, 90, tmp, lstrlen(tmp));

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_GETMINMAXINFO:
		((MINMAXINFO *)lParam)->ptMaxTrackSize.x = RectClient.right + BOARD_SIZE;
		((MINMAXINFO *)lParam)->ptMaxTrackSize.y = RectClient.bottom;
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = RectClient.right + BOARD_SIZE;
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = RectClient.bottom;
		return FALSE;
    case WM_DESTROY:
		closesocket(s);
		WSACleanup();
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
		if (LOWORD(lParam) <= BOARD_SIZE-32 && LOWORD(lParam) >= 32)
		{
			if (HIWORD(lParam) <= BOARD_SIZE-16 && HIWORD(lParam) >= 8)
			{	
				if (Board[(int)(HIWORD(lParam) - 12) / 25][(int)(LOWORD(lParam) - 28) / 23] == 0)
					Board[(int)(HIWORD(lParam) - 12) / 25][(int)(LOWORD(lParam) - 28) / 23] = 1;

				send(s, "a-Yo?", strlen("a-Yo?"), 0);
			}			
		}		
		
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_RBUTTONDOWN:
		if (LOWORD(lParam) <= BOARD_SIZE - 32 && LOWORD(lParam) >= 32)
		{
			if (HIWORD(lParam) <= BOARD_SIZE - 16 && HIWORD(lParam) >= 8)
			{
				if (Board[(int)(HIWORD(lParam) - 12) / 25][(int)(LOWORD(lParam) - 28) / 23] == 0)
				Board[(int)(HIWORD(lParam) - 12) / 25][(int)(LOWORD(lParam) - 28) / 23] = -1;


				sprintf(sendmessage, "%s", "�� ��� ����!");
				send(s, sendmessage, strlen(sendmessage), 0);
			}
		}
		
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DrawGameScene(HDC FrontDC)
{
	// Create Back Memory DC
	HDC BackMemDC = CreateCompatibleDC(GetDC(FindWindow(szWindowClass, szTitle)));
	HBITMAP hOldBitmap;

	//make BackMemDC's size properly and select source image onto BackMemDC
	HDC tmpDC = GetDC(FindWindow(szWindowClass, szTitle));
	HBITMAP hBit = CreateCompatibleBitmap(FrontDC, 500, 500);
	hOldBitmap = (HBITMAP)SelectObject(BackMemDC, hBit);
	ReleaseDC(FindWindow(szWindowClass, szTitle), tmpDC);
	DeleteObject(hBit);


	DrawBoard(BackMemDC);
	DrawStones(BackMemDC);

	BitBlt(FrontDC, 0, 0, 500, 500, BackMemDC, 0, 0, SRCCOPY);

	SelectObject(BackMemDC, hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(BackMemDC);
}

void DrawBoard(HDC BackMemDC)
{
	HBRUSH boardBG = CreateSolidBrush(RGB(248,200,120)), oldBrush;

	oldBrush = (HBRUSH)SelectObject(BackMemDC, boardBG);

	Rectangle(BackMemDC, 0, 0, 500, 500);

	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 18; j++)
		{
			Rectangle(BackMemDC, 40 + j * 23, 25 + i * 25, 41 + (j + 1) * 23, 26 + (i + 1) * 25);
		}

	oldBrush = (HBRUSH)SelectObject(BackMemDC, GetStockObject(NULL_BRUSH));
}

void DrawStones(HDC BackMemDC)
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (Board[i][j] == 1)
			{
				SelectObject(BackMemDC, GetStockObject(WHITE_BRUSH));
				Ellipse(BackMemDC, 28 + j * 23, 13 + i * 25, 29 + (j + 1) * 23, 14 + (i + 1) * 25);
			}
			else if (Board[i][j] == -1)
			{
				SelectObject(BackMemDC, GetStockObject(BLACK_BRUSH));
				Ellipse(BackMemDC, 28 + j * 23, 13 + i * 25, 29 + (j + 1) * 23, 14 + (i + 1) * 25);
			}
		}
	}
}

TCHAR* ParseMessage(char message[])
{
	TCHAR tmp[MSG_MAX_LENGTH];
	char buffer[MSG_MAX_LENGTH];
	int tmpLen;
	memset(message, 0, 201);

	std::string a;
	a.assign(message);
	char tmp2[200]; 

	if (a[0] == '$')
	{
		if (a.substr(0, a.find_first_of('$', 1)-1) == "QUIT")
		{
			PostQuitMessage(0);
			return false;
		}
	}

#ifdef _UNICODE
	tmpLen = MultiByteToWideChar(CP_ACP, 0, message, strlen(message), NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, message, strlen(message), tmp, tmpLen);
	tmp[tmpLen] = NULL;

#else
	strcpy_s(tmp, message);

#endif

	return tmp;
}
