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
	HDC hdc = GetDC(hWnd);
	if (cnt_drawPoints > 1)
	{
		MoveToEx(hdc, GetDrawStart().x, GetDrawStart().y, NULL);
		for (int i = 0; i < cnt_drawPoints; i++)
		{
			LineTo(hdc, drawPoints[i].x, drawPoints[i].y);
			MoveToEx(hdc, drawPoints[i].x, drawPoints[i].y, NULL);
		}
	}
}

void API2D::FillArea(HWND hWnd)
{
	printf("Starting FillAREA()\n");
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

	// �׸��� ��ǥ�� ���� �������� �����.
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
				Make_it_closed(lastX, lastY);
			}
		}
		// x��ǥ�� �ٸ��� y��ǥ�� ���� ��
		else if (lastY == drawPoints[0].y)
		{			
			Make_it_closed(lastX, lastY);
		}
		// �� �� �ٸ� ��
		else
		{
			Make_it_closed(lastX, lastY);			
		}
	}
	
	//������ �׸���.
	Polygon(hdc, drawPoints, cnt_drawPoints);
	
	cnt_Colliders++;
	cnt_FilledArea++;

	std::vector<POINT> tmp;
	//�ε����� x=y=idx�������� ����.
	tmp.push_back({ cnt_Colliders, cnt_Colliders });
	//�ε����� POINT�� �ִ´�. 0�� = �ܰ���
	Colliders.push_back(tmp);

	tmp.push_back({ cnt_FilledArea, cnt_FilledArea });
	FilledArea.push_back(tmp);

	//�浹ü�� �߰�
	for (int i = 0; i < cnt_drawPoints; i++)
	{
		printf("Colliders[%d].push_back(%d)......", cnt_Colliders - 1, drawPoints[i]);
		Colliders[cnt_Colliders-1].push_back(drawPoints[i]);
		printf("done!\n");
		
	}

	// �׷��� ������ �߰�
	for (int i = 0; i < cnt_drawPoints; i++)
	{
		printf("FilledArea[%d].push_back(%d)......", cnt_FilledArea - 1, drawPoints[i]);
		FilledArea[cnt_FilledArea-1].push_back(drawPoints[i]);
		printf("done!\n");

	}
	//cnt_FilledArea++;
	
	printf("freeing drawPoints.....");
	free(drawPoints);
	printf("done!\n");

	ReleaseDC(hWnd, hdc);

	setPLAYER_STATUS(IDLE);
}

//�浹ü�� ��ȣ�� �˾Ƴ���
int API2D::GetCollider_id(int lastX, int lastY)
{
	for (int i = 0; i < Colliders.size(); i++)
	{
		for (int j = 0; j < Colliders[i].size() - 1; j++)
		{
			int x1 = lastX;
			int y1 = lastY;
			int x2 = Colliders[i][j].x;
			int y2 = Colliders[i][j].y;

			int a = (y1 - y2);
			int b = (x2 - x1);
			int c = x1 * y2 - x2 * y1;

			if (abs(a * drawPoints[0].x + b * drawPoints[0].y + c) / pow((pow(a, 2) + pow(b, 2)), 2) == 0)
				return i;
		}
	}

	return 0;
}

void API2D::Make_it_closed(int lastX, int lastY)
{
	// � �浹ü���� �𸣴ϱ� ù��° �浹ü ���� ��� ���ư�
	int Collider_idx = GetCollider_id(lastX, lastY);

	for (int j = 0; j < Colliders[Collider_idx].size() - 1; j++)
	{
		if (lastX == Colliders[Collider_idx][j].x)
		{
			if (lastY > Colliders[Collider_idx][j].y)
			{
				// ������ ��ǥ�� ã�� ��ǥ ���̿� �׸��� �������� �ִ��� Ȯ��
				// ã�� ��ǥ ��ſ� �׸��� �������� �ְ� ������ ��ǥ���� ���������� ������Ʈ �Ͽ� �ִ´�. -> ���� ���� �ϼ�!
				// ������ ã�� ���� �ִ´�.
				//��� ���ǿ�

				int x1 = lastX;
				int y1 = lastY;
				int x2 = Colliders[Collider_idx][j].x;
				int y2 = Colliders[Collider_idx][j].y;

				int a = (y1 - y2);
				int b = (x2 - x1);
				int c = x1 * y2 - x2 * y1;

				if (abs(a * drawPoints[0].x + b * drawPoints[0].y + c) / pow((pow(a, 2) + pow(b, 2)), 2) == 0)
				{
					// �������� �����ų�, �������� �ִ� ���� ���� ���� ã����!
					drawPoints = (POINT*)realloc(drawPoints, ++cnt_drawPoints);
					drawPoints[cnt_drawPoints - 1] = drawPoints[0];
					lastX = drawPoints[0].x;
					lastY = drawPoints[0].y;
					// ��!
					return;
				}
				else
				{
					// ���� �� ã������ ��� ���� �߰�
					drawPoints = (POINT*)realloc(drawPoints, ++cnt_drawPoints);
					drawPoints[cnt_drawPoints - 1] = Colliders[Collider_idx][j];
					lastX = Colliders[Collider_idx][j].x;
					lastY = Colliders[Collider_idx][j].y;
				}

			}
		}
	}
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
