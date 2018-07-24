// hopscotch.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "hopscotch.h"
#include "API2D.h"
#include "Manager.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
BOOL KeyBuffer[256];

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//전역 변수 선언
API2D g_API2D;
Manager *MANAGER;

//사용자 함수 등록
void MovePlayer(HWND hWnd, int *keybuffer);
bool isCollide(HWND hWnd);
void addDrawPoint();
void updateDrawPoint();
void reternPlayer(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOPSCOTCH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOPSCOTCH));

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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOPSCOTCH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HOPSCOTCH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//제자리일 경우, 애니메이션을 하기 위한 프레임 스킵용 임시 카운터
	static int idle_cnt = 0;
	static RECT tmpRect;
	std::stringstream ss;

    switch (message)
    {   
	case WM_CREATE:
	{
		MANAGER->GetInstance();
		g_API2D.Init(hWnd);		
		SetTimer(hWnd, 1, 15, NULL);
		GetClientRect(hWnd, &tmpRect); 
	}
		break;
    case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		g_API2D.Draw(hdc);
		g_API2D.DrawLine(hWnd);
		EndPaint(hWnd, &ps);
	}
		break;
    case WM_DESTROY:
		KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
	case WM_GETMINMAXINFO:		
		//윈도우 창 크기 변화 방지, 
		//16 : 창 두께
		//58 : 창 두께, 타이틀 바, 메뉴 바
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = g_API2D.getWidthMax() + 16;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = g_API2D.getWidthMax() + 16;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = g_API2D.getHeightMax() + 58;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = g_API2D.getHeightMax() + 58;
		return false;
	case WM_TIMER:
		idle_cnt++;
		if (g_API2D.getPLAYER_STATUS() == IDLE && idle_cnt % 11 >= 10)
			g_API2D.AddFrame(1);

		if (idle_cnt > 10000)
			idle_cnt = 0;
		
		if (g_API2D.getPLAYER_STATUS() == RETURNING)
			reternPlayer(hWnd);

		if (g_API2D.getPLAYER_STATUS() == DRAWING_DONE)
			g_API2D.FillArea(hWnd);
			
		g_API2D.Update(hWnd);
		InvalidateRgn(hWnd, 0, false);
		break;
	case WM_KEYDOWN:
		
		if (g_API2D.getPLAYER_STATUS() != RETURNING)
		{
			KeyBuffer[wParam] = TRUE;

			if ((wParam == VK_SPACE) && (g_API2D.cnt_drawPoints <1) )
			{

				//임시 벡터.
				std::vector<POINT> vPtmp;
				//인덱스를 x=y=idx형식으로 넣자.
				vPtmp.push_back({ g_API2D.cnt_Colliders, g_API2D.cnt_Colliders });
				//인덱스용 POINT를 넣는다. 0번 = 외곽선
				g_API2D.Colliders.push_back(vPtmp);
				g_API2D.cnt_Colliders++;
				//외곽선 좌표 입력 시작
				g_API2D.Colliders[g_API2D.cnt_Colliders - 1].push_back({ 0,0 });
				g_API2D.Colliders[g_API2D.cnt_Colliders - 1].push_back({ g_API2D.getWidthMax(), 0 });
				g_API2D.Colliders[g_API2D.cnt_Colliders - 1].push_back({ g_API2D.getWidthMax(), g_API2D.getHeightMax() });
				g_API2D.Colliders[g_API2D.cnt_Colliders - 1].push_back({ 0, g_API2D.getHeightMax() });
				g_API2D.Colliders[g_API2D.cnt_Colliders - 1].push_back({ 0,0 });	//좌표 계산이 쉽도록 위해 마지막에 첫 좌표를 하나 더 넣음


				POINT tmp;
				g_API2D.drawPoints = (POINT*)calloc(++g_API2D.cnt_drawPoints, sizeof(POINT));
				tmp.x = g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].x = g_API2D.GetPosX();
				tmp.y = g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].y = g_API2D.GetPosY();
				g_API2D.SetDrawStart(tmp);
				system("cls");
				printf("스페이스 바 눌림 \ndrawPoints : %d", g_API2D.cnt_drawPoints);
			}

			MovePlayer(hWnd, KeyBuffer);
		}		
			
		break;
	case WM_KEYUP:
		KeyBuffer[wParam] = FALSE;

		if (wParam == VK_SPACE)
			if (g_API2D.getPLAYER_STATUS() == DRAWING)
			{
				g_API2D.setPLAYER_STATUS(RETURNING);
				printf("복귀 시작!\n");
				reternPlayer(hWnd);
			}
			else
				g_API2D.setPLAYER_STATUS(IDLE);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void MovePlayer(HWND hWnd, int* Keybuffer)
{
	static POINT curpos;
	static POINT newpos;
	curpos.x = g_API2D.GetPosX();
	curpos.y = g_API2D.GetPosY();
	static int cur_State = g_API2D.getPLAYER_STATUS();
	static int newState;

	//if (g_API2D.getPLAYER_STATUS() == DRAWING)
	if (Keybuffer[VK_SPACE])
		if (cur_State != DRAWING)	//상태 전환 : 이동 -> 그리기
		{
			//현재 좌표를 그리기 좌표들의 첫번째에 넣는다.
			g_API2D.drawPoints = (POINT*)realloc(g_API2D.drawPoints, (g_API2D.cnt_drawPoints) * sizeof(POINT));
			g_API2D.drawPoints[g_API2D.cnt_drawPoints-1] = curpos;

			// 현재 상태를 그리기로 변경해준다.
			g_API2D.setPLAYER_STATUS(DRAWING);
		}		

	if (Keybuffer[VK_UP])
	{
		newpos.x = curpos.x;
		newpos.y = curpos.y - g_API2D.getPLAYER_SPEED();
	
 		if (newpos.y <= 0)
			newpos.y = 0;
		else if (newpos.y >= g_API2D.getHeightMax())
			newpos.y = g_API2D.getHeightMax();

		if (g_API2D.getFacingDir() != FACING_UP)
		{
			g_API2D.setFacingDir(FACING_UP);	
			addDrawPoint();
			g_API2D.AddFrame(1);
			g_API2D.SetPosX(newpos.x);
			g_API2D.SetPosY(newpos.y);			
		}
		else
		{
			g_API2D.AddFrame(1);
			g_API2D.SetPosX(newpos.x);
			g_API2D.SetPosY(newpos.y);
			updateDrawPoint();
		}
		
	}
	else if (Keybuffer[VK_RIGHT])
	{
		newpos.x = curpos.x + g_API2D.getPLAYER_SPEED();
		newpos.y = curpos.y;

		if (newpos.x <= 0 || newpos.x >= g_API2D.getWidthMax())
			newpos.x = curpos.x;

		if (g_API2D.getFacingDir() != FACING_RIGHT)
		{
			g_API2D.setFacingDir(FACING_RIGHT);
			// 꺽인 지점을 좌표로 추가하고
			addDrawPoint();
			g_API2D.AddFrame(1);
			g_API2D.SetPosX(newpos.x);
			g_API2D.SetPosY(newpos.y);
			//새 지점을 넣고
			addDrawPoint();
			// 꺽인 지점의 이동 후 좌표를 넣는다.
			updateDrawPoint();
		}
		else
		{
			g_API2D.AddFrame(1);
			g_API2D.SetPosX(newpos.x);
			g_API2D.SetPosY(newpos.y);
			updateDrawPoint();
		}
		
	}
	else if (Keybuffer[VK_DOWN])
	{
		newpos.x = curpos.x;
		newpos.y = curpos.y + g_API2D.getPLAYER_SPEED();

		if (newpos.y <= 0 || newpos.y >= g_API2D.getHeightMax())
			newpos.y = curpos.y;

		if (g_API2D.getFacingDir() != FACING_DOWN)
		{
			g_API2D.setFacingDir(FACING_DOWN);
			addDrawPoint();
			g_API2D.AddFrame(1);
			g_API2D.SetPosX(newpos.x);
			g_API2D.SetPosY(newpos.y);
		}
		else
		{
			g_API2D.AddFrame(1);
			g_API2D.SetPosX(newpos.x);
			g_API2D.SetPosY(newpos.y);
			updateDrawPoint();
		}
	}
	else if (Keybuffer[VK_LEFT])
	{
		newpos.x = curpos.x - g_API2D.getPLAYER_SPEED();
		newpos.y = curpos.y;

		if (newpos.x <= 0 || newpos.x >= g_API2D.getWidthMax())
			newpos.x = curpos.x;

		if (g_API2D.getFacingDir() != FACING_LEFT)
		{
			g_API2D.setFacingDir(FACING_LEFT);
			addDrawPoint();
			g_API2D.AddFrame(1);
			g_API2D.SetPosX(newpos.x);
			g_API2D.SetPosY(newpos.y);
		}
		else
		{
			g_API2D.AddFrame(1);
			g_API2D.SetPosX(newpos.x);
			g_API2D.SetPosY(newpos.y);
			updateDrawPoint();
		}
	}



	if (g_API2D.getPLAYER_STATUS() == DRAWING)
	{		
		if (g_API2D.cnt_drawPoints > 0)
		{
			printf("cnt_drawPoints : %d\n", g_API2D.cnt_drawPoints);
			for (int i = 0; i < g_API2D.cnt_drawPoints; i++)
			{
				printf("%d : %d, %d\n", i, g_API2D.drawPoints[i].x, g_API2D.drawPoints[i].y);
			}
		}
	}

	if (isCollide(hWnd))
	{
		g_API2D.setPLAYER_STATUS(DRAWING_DONE);
	}

}

bool isCollide(HWND hWnd) {

 	int curX = g_API2D.GetPosX();
	int curY = g_API2D.GetPosY();

	if (g_API2D.cnt_drawPoints > 1)
	{
		if (g_API2D.getPLAYER_STATUS() == DRAWING)
		{
			POINT tmp;
			tmp = g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1];

			for (int i = 0; i < g_API2D.Colliders.size(); i++)
			{
				for (int j = 0; j < g_API2D.Colliders[i].size() - 1; j++)
				{
					int x1 = g_API2D.Colliders[i][j].x;
					int y1 = g_API2D.Colliders[i][j].y;
					int x2 = g_API2D.Colliders[i][j + 1].x;
					int y2 = g_API2D.Colliders[i][j + 1].y;
					int a = abs(y1 - y2);
					int b = abs(x2 - x1);
					int c = x1 * y2 - x2 * y1;

					if (abs(a * curX + b * curY + c) / pow((pow(a, 2) + pow(b, 2)), 2) == 0);
					{
						addDrawPoint();
						return true;
					}
				}
			}
		}
	}

	return false;
}


//현재 캐릭터 위치의 x좌표 y좌표를 그리기 할 좌표 목록에 추가한다.
void addDrawPoint()
{
	if (g_API2D.getPLAYER_STATUS() == DRAWING)
	{		
		g_API2D.drawPoints = (POINT*)realloc(g_API2D.drawPoints, sizeof(POINT) * (++g_API2D.cnt_drawPoints));
		g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].x = g_API2D.GetPosX();
		g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].y = g_API2D.GetPosY();
	}
}

void updateDrawPoint()
{
	if (g_API2D.cnt_drawPoints > 0)
	{
		g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].x = g_API2D.GetPosX();
		g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].y = g_API2D.GetPosY();
	}
}

void reternPlayer(HWND hWnd)
{

		//편의상 현재 좌표를 각각 저장한다.
		 int curX = g_API2D.GetPosX();
		 int curY = g_API2D.GetPosY();
		static int speed = g_API2D.getPLAYER_SPEED();

		//목표 지점을 설정한다.
		POINT dest; 

		dest.x = g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].x;
		dest.y = g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].y;
		if (g_API2D.cnt_drawPoints < 1)
		{
			g_API2D.setPLAYER_STATUS(IDLE);
			g_API2D.cnt_drawPoints = 0;
			printf("\n[복귀 완료!]\n");
			free(g_API2D.drawPoints);
			return;
		}


		//이동 하는 종안 꺄아~~ 하고 회전회전
		g_API2D.setFacingDir(rand() % 4 + 1);

		//목표 지점까지 좌표 이동

		if (curX > dest.x)
		{
			curX -= speed;

			if (curX <= dest.x)
				curX = dest.x;
		}
		else if (curX < dest.x)
		{	
			curX += speed;

			if (curX >= dest.x)
				curX = dest.x;
		}
		
		if (curX == dest.x)
		{
			if (curY > dest.y)
			{
				curY -= speed;

				if (curY <= dest.y)
					curY = dest.y;
			}
			else if (curY < dest.y)
			{
				curY += speed;

				if (curY >= dest.y)
					curY = dest.y;
			}
		}
		
		g_API2D.SetPosX(curX);
		g_API2D.SetPosY(curY);
		
		if ((curX == dest.x) && (curY == dest.y))
		{
			printf(" [ 완료!] \n");

			if (g_API2D.cnt_drawPoints > 0)
			{
				g_API2D.drawPoints = (POINT*)realloc(g_API2D.drawPoints, sizeof(POINT) * (g_API2D.cnt_drawPoints--));
				if (g_API2D.cnt_drawPoints >= 1)
					printf("다음 목표 지점(%d, %d)으로 이동중", g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].x, g_API2D.drawPoints[g_API2D.cnt_drawPoints - 1].y);
			}
			else
			{
				g_API2D.setPLAYER_STATUS(IDLE);
				g_API2D.cnt_drawPoints = 0;
				free(g_API2D.drawPoints);
				printf("\n[복귀 완료!]\n");

				return;
			}
		}
		else
			printf(".");
		InvalidateRgn(hWnd, NULL, TRUE);

}

