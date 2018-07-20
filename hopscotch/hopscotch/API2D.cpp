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
	
	//�ӽ� ����.
	std::vector<POINT> tmp;
	//�ε����� x=y=idx�������� ����.
	tmp.push_back({ cnt_Colliders, cnt_Colliders });
	//�ε����� POINT�� �ִ´�. 0�� = �ܰ���
	Colliders.push_back(tmp);
	cnt_Colliders++;
	//�ܰ��� ��ǥ �Է� ����
	Colliders[cnt_Colliders-1].push_back({ 0,0 });
	Colliders[cnt_Colliders-1].push_back({getWidthMax(), 0 });
	Colliders[cnt_Colliders-1].push_back({ getWidthMax(), getHeightMax()});
	Colliders[cnt_Colliders-1].push_back({0, getHeightMax()});
	Colliders[cnt_Colliders - 1].push_back({ 0,0 });	//��ǥ ����� ������ ���� �������� ù ��ǥ�� �ϳ� �� ����
	
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

	//�÷��̾� �ܱ� ǥ��
	HDC hdc = GetDC(hWnd);
	HDC hMemDC2;
	HBITMAP hLifeBitmap;

	hMemDC2 = CreateCompatibleDC(hdc);
	hLifeBitmap = (HBITMAP)SelectObject(hMemDC2, hBit2);

	for (int i = 0; i < this->GetLifeStock(); i++)
		TransparentBlt(hdc, 10 + i * SPRITE_WIDTH, 25, SPRITE_WIDTH, SPRITE_HEIGHT,
			hMemDC2,
			26, 0, 25, 30, RGB(255, 0, 255));

	//���� ���� �̹����� �޸𸮿� �׷ȴ� DC�� �����Ѵ�.
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
	
	
	//��� �̹����� �׸���.
	TransparentBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, bx,by, RGB(255, 0, 255));
	//��� �̹����� �޸𸮿� �׷ȴ� DC�� �����Ѵ�.
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
	
	// ���� ��ǥ�� ���ư��鼭 �������� ã�Ƽ� ����Ʈ�� �ְ� �ٰ����� �׸���.
	// ���� ������ ��������,�� �Ǵ� �Ʒ� ������ X -> Y ->X ������
	// ���� �Ǵ� �������̾����� Y -> X -> Y ������
	
	// ������ ��ǥ(�浹 �� ��ǥ)�� �������� ������ �Ǵ��Ѵ�.
	// �ƴϸ� ���������� �̵��ϸ鼭 �浹ü�� ��ǥ���� ã�´�. (���� ���� �ִ� ��ǥ �� x y�� ���Ͽ� ã�´�.)

	int horizontal;
	int vertical;

	int lastX = drawPoints[cnt_drawPoints - 1].x;
	int lastY = drawPoints[cnt_drawPoints - 1].y;

	// ���� ���� Ȯ��
	if (lastX - drawPoints[0].x > 0)
		horizontal = 1;
	else
		horizontal = -1;

	// ���� ���� Ȯ��
	if (lastY - drawPoints[0].y > 0)
		vertical = -1;
	else
		vertical = 1;


	while ((lastY != drawPoints[0].y) && (lastX != drawPoints[0].x))
	{
		// X��ǥ�� ���� ��
		if (lastX == drawPoints[0].x)
		{
			if (lastY == drawPoints[0].y)	//���� ��ǥ
				Polygon(hdc, drawPoints, cnt_drawPoints);		// ���� ���� = �׸���!
			// ���� ������ ��ǥ
			else    
			{
				//�Ʒ���~
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
									// ������ ��ǥ�� ã�� ��ǥ ���̿� �׸��� �������� �ִ��� Ȯ��
									// ã�� ��ǥ ��ſ� �׸��� �������� �ְ� ������ ��ǥ���� ���������� ������Ʈ �Ͽ� �ִ´�. -> ���� ���� �ϼ�!
									// ������ ã�� ���� �ִ´�.

									//��� ���ǿ�
									
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
				//����~~
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
		// y��ǥ�� ���� ��
		else if (lastY == drawPoints[0].y)
		{
		}
		// �� �� �ٸ� ��
		else
		{
			// ���� ���� Ȯ��
			if (lastX - drawPoints[0].x > 0)
				horizontal = 1;
			else
				horizontal = -1;

			// ���� ���� Ȯ��
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
