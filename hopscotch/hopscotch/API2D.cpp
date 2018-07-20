#include "stdafx.h"
#include "API2D.h"
#include "Manager.h"
#pragma comment(lib, "msimg32.lib")

API2D::API2D() : cur_posX(0), cur_posY(0), CurFrame(1)
{
	AddLifeStock(3);
	strText = NULL;
}


API2D::~API2D()
{
}

void API2D::Init(HWND hWnd)
{
	hBit = (HBITMAP)LoadImage(NULL, TEXT("masaru.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit, sizeof(BITMAP), &bit);

	hBit2 = (HBITMAP)LoadImage(NULL, TEXT("PC_SPRITES.bmp"),
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBit2, sizeof(BITMAP), &bit2);
	
	//임시 벡터.
	std::vector<POINT> tmp;
	//인덱스를 x=y=idx형식으로 넣자.
	tmp.push_back({ cnt_Colliders, cnt_Colliders });
	//인덱스용 POINT를 넣는다. 0번 = 외곽선
	Colliders.push_back(tmp);
	cnt_Colliders++;
	//외곽선 좌표 입력 시작
	Colliders[cnt_Colliders-1].push_back({ 0,0 });
	Colliders[cnt_Colliders-1].push_back({getWidthMax(), 0 });
	Colliders[cnt_Colliders-1].push_back({ getWidthMax(), getHeightMax()});
	Colliders[cnt_Colliders-1].push_back({0, getHeightMax()});
	Colliders[cnt_Colliders - 1].push_back({ 0,0 });	//좌표 계산이 쉽도록 위해 마지막에 첫 좌표를 하나 더 넣음
	
}

void API2D::Update(HWND hwnd)
{
	UpdateText();
	UpdataAnimation();
	UpdateUI(hwnd);
}

void API2D::UpdataAnimation()
{
	if (getPLAYER_STATUS() == MOVING || getPLAYER_STATUS() == DRAWING)
	{
		if (CurFrame > RUN_FRAME_MAX)
			CurFrame = RUN_FRAME_MIN;
	}
}

void API2D::UpdateText()
{}

void API2D::UpdateUI(HWND hWnd)
{

	//플레이어 잔기 표시
	HDC hdc = GetDC(hWnd);
	HDC hMemDC2;
	HBITMAP hLifeBitmap;

	hMemDC2 = CreateCompatibleDC(hdc);
	hLifeBitmap = (HBITMAP)SelectObject(hMemDC2, hBit2);

	for (int i = 0; i < this->GetLifeStock(); i++)
		TransparentBlt(hdc, 10 + i * SPRITE_WIDTH, 25, SPRITE_WIDTH, SPRITE_HEIGHT,
			hMemDC2,
			26, 0, 25, 30, RGB(255, 0, 255));

	//남은 생명 이미지를 메모리에 그렸던 DC를 삭제한다.
	SelectObject(hMemDC2, hLifeBitmap);
	DeleteDC(hMemDC2);
	ReleaseDC(hWnd, hdc);

}

void API2D::Draw(HDC hdc)
{
	HDC hMemDC;	
	HBITMAP hOldBitmap;
	int bx, by;
	bx = bit.bmWidth;
	by = bit.bmHeight;
	setWidthMax(bx);
	setHeightMax(by);

	hMemDC = CreateCompatibleDC(hdc);
	GetStockObject(NULL_BRUSH);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit);	
	
	
	//배경 이미지를 그린다.
	TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bx,by, RGB(255, 0, 255));
	//배경 이미지를 메모리에 그렸던 DC를 삭제한다.
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

	DrawAnimation(hdc);

}

void API2D::DrawAnimation(HDC hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;
	hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBit2);

	bx = SPRITE_WIDTH;
	by = SPRITE_HEIGHT;

	int StartX = CurFrame * bx;
	int StartY = (FacingDir-1) * SPRITE_HEIGHT;

	TransparentBlt(hdc, cur_posX- SPRITE_WIDTH /2, cur_posY- SPRITE_HEIGHT /2, bx, by, hMemDC,
		StartX, StartY, bx, by,
		RGB(255, 0, 255));

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
}

void API2D::PrintText(HDC hdc)
{
}

void API2D::SetPosX(int x)
{
	this->cur_posX = x;
}

void API2D::SetPosY(int y)
{
	this->cur_posY = y;
}

void API2D::SetDrawStart(POINT StartPos)
{
	this->DrawStart.x = StartPos.x;
	this->DrawStart.y = StartPos.y;
}

POINT API2D::GetDrawStart()
{	
	return this->DrawStart;
}


void API2D::DrawLine(HWND hWnd)
{
	
}

void API2D::FillArea(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	
	// 시작 좌표로 돌아가면서 꼭지점을 찾아서 리스트에 넣고서 다각형을 그린다.
	// 가던 방향을 기준으로,위 또는 아래 였으면 X -> Y ->X 순으로
	// 왼쪽 또는 오른쪽이었으면 Y -> X -> Y 순으로
	
	// 마지막 좌표(충돌 난 좌표)가 시작점과 같은지 판단한다.
	// 아니면 시작점으로 이동하면서 충돌체의 좌표들을 찾는다. (동일 선상에 있는 좌표 중 x y를 비교하여 찾는다.)

	int horizontal;
	int vertical;

	int lastX = drawPoints[cnt_drawPoints - 1].x;
	int lastY = drawPoints[cnt_drawPoints - 1].y;

	// 수평 방향 확인
	if (lastX - drawPoints[0].x > 0)
		horizontal = 1;
	else
		horizontal = -1;

	// 수직 방향 확인
	if (lastY - drawPoints[0].y > 0)
		vertical = -1;
	else
		vertical = 1;


	while ((lastY != drawPoints[0].y) && (lastX != drawPoints[0].x))
	{
		// X좌표가 같을 때
		if (lastX == drawPoints[0].x)
		{
			if (lastY == drawPoints[0].y)	//같은 좌표
				Polygon(hdc, drawPoints, cnt_drawPoints);		// 닫힌 도형 = 그린다!
			// 같은 선상의 좌표
			else    
			{
				//아래로~
				if (vertical > 0)
				{
					for (int i = 0; i < Colliders.size(); i++)
					{
						for (int j = 0; j < Colliders[i].size() - 1; j++)
						{
							if (lastX == Colliders[i][j].x)
							{
								if (lastY > Colliders[i][j].y)
								{							
									// 마지막 좌표와 찾은 좌표 사이에 그리기 시작점이 있는지 확인
									// 찾은 좌표 대신에 그리기 시작점을 넣고 마지막 좌표값을 시작점으로 업데이트 하여 넣는다. -> 닫힌 도형 완성!
									// 없으면 찾은 점을 넣는다.

									//계산 편의용
									
									int x1 = lastX;
									int y1 = lastY;
									int x2 = Colliders[i][j].x;
									int y2 = Colliders[i][j].y;
									
									int a = (y1 - y2);
									int b = (x2 - x1);
									int c = x1 * y2 - x2 * y1;

									if (abs(a * drawPoints[0].x + b * drawPoints[0].y + c) / pow((pow(a, 2) + pow(b, 2)), 2) == 0);
									{
										drawPoints = (POINT*)realloc(drawPoints, ++cnt_drawPoints);
										drawPoints[cnt_drawPoints - 1] = drawPoints[0];
										lastX = drawPoints[0].x;
										lastY = drawPoints[0].y;
									}
									else
									{
										drawPoints = (POINT*)realloc(drawPoints, ++cnt_drawPoints);
										drawPoints[cnt_drawPoints - 1] = Colliders[i][j];
										lastX = Colliders[i][j].x;
										lastY = Colliders[i][j].y;
									}
									//








								}
							}
						}
					}
				}
				//위로~~
				else
				{
					for (int i = 0; i < Colliders.size(); i++)
					{
						for (int j = 0; j < Colliders[i].size() - 1; j++)
						{
							if (lastX == Colliders[i][j].x)
							{
								if (lastY < Colliders[i][j].y)
								{
									drawPoints = (POINT*)realloc(drawPoints, ++cnt_drawPoints);
									drawPoints[cnt_drawPoints - 1] = Colliders[i][j];
									lastX = Colliders[i][j].x;
									lastY = Colliders[i][j].y;
								}
							}
						}
					}
				}
			}
		}
		// y좌표가 같을 때
		else if (lastY == drawPoints[0].y)
		{
		}
		// 둘 다 다를 때
		else
		{
			// 수평 방향 확인
			if (lastX - drawPoints[0].x > 0)
				horizontal = 1;
			else
				horizontal = -1;

			// 수직 방향 확인
			if (lastY - drawPoints[0].y > 0)
				vertical = -1;
			else
				vertical = 1;

			
			for (int i = 0; i < Colliders.size(); i++)
			{
				for (int j = 0; j < Colliders[i].size() - 1; i++)
				{

				}
			}






		}

	}
	

	Polygon(hdc, drawPoints, cnt_drawPoints);
	
	for (int i = 0; i < cnt_drawPoints; i++)
	{
		FilledArea[cnt_FilledArea].push_back(drawPoints[i]);
	}
	cnt_FilledArea++;
	
	free(drawPoints);
	ReleaseDC(hWnd, hdc);
}

int API2D::GetPosX()
{
	return cur_posX;
}

int API2D::GetPosY()
{
	return cur_posY;
}

void API2D::AddFrame(int x)
{
	if (CurFrame + x > RUN_FRAME_MAX)
	{
		CurFrame = RUN_FRAME_MIN;
	}
	else
		CurFrame += x;
}

void API2D::setFacingDir(int FacingDir)
{
	this->FacingDir = FacingDir;
}

int API2D::getFacingDir()
{
	return this->FacingDir;
}
