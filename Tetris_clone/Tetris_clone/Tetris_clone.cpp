// Tetris_clone.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Tetris_clone.h"
#include "Manager.h"
#include "tBlocks.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
Manager *Mgr;									// 게임 매니져
RECT RectView;


//사용자 함수
void DrawTetrimino(HDC hdc);
void DrawStage(HDC hdc);
std::vector<RECT> TetrinimoBoxes;
tBlocks Tetrimino;
RECT Scores = { 10,10,100,30 };
char tmp_msg[100];
//void SetStage();

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
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TETRISCLONE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRISCLONE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRISCLONE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TETRISCLONE);
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

	static int cnt = 0;
    switch (message)
    {
	case WM_CREATE:		
		Mgr->GetInstance();
		Tetrimino.InitTetrimino();
		SetTimer(hWnd, 1, 15, NULL);
		SetTimer(hWnd, 2, Tetrimino.GetDownSpeed(), NULL);
		GetClientRect(hWnd, &RectView);		
		MoveWindow(hWnd, 10, 10, 468, 748, TRUE);
		break;
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 468;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 748;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 468;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 748;
		return false;
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
			HDC mDC = CreateCompatibleDC(hdc);

			HBITMAP backBit = CreateCompatibleBitmap(hdc, RectView.right, RectView.bottom);			
			HBITMAP oldBit = (HBITMAP)SelectObject(mDC, backBit);

			DrawStage(mDC);

			//BitBlt(hdc, 0, 0, PLAY_AREA_WIDTH * BOX_SIZE, PLAY_AREA_HEIGHT * BOX_SIZE, mDC, 0, 0, SRCCOPY);
			BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, mDC, 0, 0, SRCCOPY);

			//TransparentBlt(hdc, 0, 0, 450, 690, mDC, 0, 0, 450, 690, RGB(0, 0, 0));
			SelectObject(mDC, oldBit);
			DeleteObject(backBit);
			DeleteDC(mDC);
            EndPaint(hWnd, &ps);

			//for debug
			system("cls");
			for (int i = 0; i < PLAY_AREA_HEIGHT; i++)
			{
				for (int j = 0; j < PLAY_AREA_WIDTH; j++)
				{
					printf("%2x", Tetrimino.PLAY_AREA_STATUS[i][j]);
				}
				printf("\n");
			}
			printf("CurX = %2d, CurY = %2d\n", Tetrimino.GetCurX(), Tetrimino.GetCurY());
			printf("landing Status : ");
			if (!Tetrimino.isLanded())
				printf("not "); 
			printf("Landed\n");
				
        }
        break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			Tetrimino.MoveRight();
			break;
		case VK_LEFT:
			Tetrimino.MoveLeft();
			break;
		case VK_ESCAPE:
			Tetrimino.InitTetrimino();
			break;
		case VK_DOWN:
			KillTimer(hWnd, 2);
			Tetrimino.Down();
			SetTimer(hWnd, 2, Tetrimino.GetDownSpeed(), NULL);
			break;
		case VK_UP:
			Tetrimino.Rotate();
			break;
		case VK_SPACE:
			while (!Tetrimino.isLanded())
			{
   				Tetrimino.HardDrop();
			}			
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 2, Tetrimino.GetDownSpeed(), NULL);
			break;
		case VK_ADD:
			if (Tetrimino.GetDownSpeed() <= 500)
				Tetrimino.SetDownSpeed(200);
			else 
				Tetrimino.SetDownSpeed(Tetrimino.GetDownSpeed() - 100);
			break;
		case VK_SUBTRACT:
			if (Tetrimino.GetDownSpeed() >= 2000)
				Tetrimino.SetDownSpeed(2000);
			else
				Tetrimino.SetDownSpeed(Tetrimino.GetDownSpeed() + 100);
			break;
		case VK_RETURN:
			Tetrimino.NewPlayArea();
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			InvalidateRgn(hWnd, NULL, FALSE);
			break;
		case 2:
			Tetrimino.Down();
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 2, Tetrimino.GetDownSpeed(), NULL);
			InvalidateRgn(hWnd, NULL, FALSE);
			break;
		}
		break;
    case WM_DESTROY:
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

void DrawTetrimino(HDC hdc)
{	
	for (int i = 0; i < 4; i++)
	{
			HBRUSH MyBrush, OldBrush;
			std::vector<int> cRGB;

			cRGB = Tetrimino.GetBlockColor(Tetrimino.GetShape());
			MyBrush = CreateSolidBrush(RGB(cRGB[0], cRGB[1], cRGB[2]));
			OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		
			Rectangle(hdc, TetrinimoBoxes[i].left, TetrinimoBoxes[i].top, TetrinimoBoxes[i].right, TetrinimoBoxes[i].bottom);

			SelectObject(hdc, OldBrush);
			DeleteObject(MyBrush);		
	}
}

// Draw All stage area objects.
// Walls, Ground, Droped tetriminos, Player controlled tetriminos.
void DrawStage(HDC hdc)
{
	HBRUSH MyBrush_walls, MyBrush_occupied, MyBrush_tetrimino, OldBrush;
	std::vector<int> cRGB;
	cRGB = Tetrimino.GetBlockColor(Tetrimino.GetShape());

	MyBrush_occupied = CreateSolidBrush(RGB(cRGB[0] / 2, cRGB[1] / 2, cRGB[2] / 2));
	MyBrush_tetrimino = CreateSolidBrush(RGB(cRGB[0], cRGB[1], cRGB[2]));
	MyBrush_walls = CreateSolidBrush(RGB(128, 128, 128));

	int mod = BOX_SIZE / 2;
	
	for (int i = 0; i < PLAY_AREA_HEIGHT; i++)
	{
		for (int j = 0; j < PLAY_AREA_WIDTH; j++)
		{
			// draw Walls and ground.
			if ((Tetrimino.PLAY_AREA_STATUS[i][j] == WALL) || (Tetrimino.PLAY_AREA_STATUS[i][j] == GROUND))
			{
				OldBrush = (HBRUSH)SelectObject(hdc, MyBrush_walls);

				if (j == 0)
					Rectangle(hdc, 
						PLAY_AREA_MARGIN + j * BOX_SIZE - mod, PLAY_AREA_MARGIN + i * BOX_SIZE - mod, 
						PLAY_AREA_MARGIN + j * BOX_SIZE + mod, PLAY_AREA_MARGIN + i * BOX_SIZE + mod);
				else
					Rectangle(hdc, 
						PLAY_AREA_MARGIN + j * BOX_SIZE - mod, PLAY_AREA_MARGIN + i * BOX_SIZE - mod, 
						PLAY_AREA_MARGIN + j * BOX_SIZE + mod, PLAY_AREA_MARGIN + i * BOX_SIZE + mod);
				SelectObject(hdc, OldBrush);
			}

			// draw occipied spaces.
			if ((Tetrimino.PLAY_AREA_STATUS[i][j] >= OCCUPIED_0) && (Tetrimino.PLAY_AREA_STATUS[i][j] <= OCCUPIED_6))
			{
				cRGB = Tetrimino.GetBlockColor(Tetrimino.PLAY_AREA_STATUS[i][j]-2);
				MyBrush_occupied = CreateSolidBrush(RGB(cRGB[0] / 2, cRGB[1] / 2, cRGB[2] / 2));
				OldBrush = (HBRUSH)SelectObject(hdc, MyBrush_occupied);

				Rectangle(hdc,
					PLAY_AREA_MARGIN + j * BOX_SIZE - mod, PLAY_AREA_MARGIN + i * BOX_SIZE - mod, 
					PLAY_AREA_MARGIN + j * BOX_SIZE + mod, PLAY_AREA_MARGIN + i * BOX_SIZE + mod);

				SelectObject(hdc, OldBrush);
			}

			// draw Tetrimino.
			if ((Tetrimino.PLAY_AREA_STATUS[i][j] == TETRIMINO))
			{
				OldBrush = (HBRUSH)SelectObject(hdc, MyBrush_tetrimino);

				Rectangle(hdc,
					PLAY_AREA_MARGIN + j * BOX_SIZE - mod, PLAY_AREA_MARGIN + i * BOX_SIZE - mod,
					PLAY_AREA_MARGIN + j * BOX_SIZE + mod, PLAY_AREA_MARGIN + i * BOX_SIZE + mod);

				SelectObject(hdc, OldBrush);

			}

		}
	}
	
	DeleteObject(MyBrush_walls);
	DeleteObject(MyBrush_occupied);
	DeleteObject(MyBrush_tetrimino);

}

