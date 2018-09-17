// wub32API3D.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "win32API3D.h"
#include "cMainGame.h"
#include "cMatrix.h"
#include "cVector3.h"

#define MAX_LOADSTRING 100

// 
HWND g_hWnd;
cMainGame* g_pMainGame;

//


// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

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
    LoadStringW(hInstance, IDC_WUB32API3D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	g_pMainGame = new cMainGame;
	g_pMainGame->Setup();

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WUB32API3D));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
	// -> ����
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	delete g_pMainGame;

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WUB32API3D));
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

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}


void tmp_func()
{
	return;
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
	//if (g_pMainGame)
	{
		//g_pMainGame->WndProc(hWnd, message, wParam, lParam);
	}
	//else
	{
		switch (message)
		{
		case WM_CREATE:
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
			if (g_pMainGame)
			{
				g_pMainGame->GetClientArea(hWnd);
				g_pMainGame->Render(hdc);
			}
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_CHAR:			
			switch (wParam)
			{
			case 'd':
				g_pMainGame->SetRotationY(g_pMainGame->GetRotationY() + 15.0f);
				break;
			case 'a':
				g_pMainGame->SetRotationY(g_pMainGame->GetRotationY() - 15.0f);
				break;
			case 'x':
			{
				cVector3 tmp_scale = { 0.1,0.1,0.1 };
				g_pMainGame->SetMyScale(g_pMainGame->GetMyScaleVector() + tmp_scale);
			}
				break;
			case 'z':
			{
				cVector3 tmp_scale = { 0.1,0.1,0.1 };
				g_pMainGame->SetMyScale(g_pMainGame->GetMyScaleVector() - tmp_scale);
			}
				break;
			case 'w':
				g_pMainGame->SetTransformXYZ(g_pMainGame->GetTransformXYZ().x, g_pMainGame->GetTransformXYZ().y, g_pMainGame->GetTransformXYZ().z - 0.2f);
				break;
			case 's':
				g_pMainGame->SetTransformXYZ(g_pMainGame->GetTransformXYZ().x, g_pMainGame->GetTransformXYZ().y, g_pMainGame->GetTransformXYZ().z + 0.2f);
				break;
			case 'r':
				g_pMainGame->SetRotationY(0.0f);
				g_pMainGame->SetMyScale(1.0f, 1.0f, 1.0f);
				g_pMainGame->SetTransformXYZ(0,0,0);
				break;
			}
			
			InvalidateRgn(hWnd, NULL, FALSE);

			break;
			
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

    return 0;
}
