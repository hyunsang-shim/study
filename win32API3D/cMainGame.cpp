#include "stdafx.h"
#include "cMainGame.h"
#include "cMatrix.h"

cMainGame::cMainGame()
	:m_hBitmap(NULL),
	m_vEye(0, 0, -5),
	m_vLookAt(0, 0, 0),
	m_vUp(0, 1, 0),
	m_vPosition(0, 0, 0),
	m_fCameraDistance(5.0f),
	m_isLButtonDown(false),
	m_vCamRotAngle(0, 0, 0),
	m_fBoxRotY(0.0f),
	m_vBoxDirection(0,0,1),
	m_fScale(1.0f)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}

cMainGame::~cMainGame()
{}

void cMainGame::Setup()
{
	// set...
	// 1. draw
	// 2. Vertex
	// ������ ��ǥ�� ���Ѵ�
	{
		// ���� -> �»� -> ��� -> ����
		// ����
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));

	}

	// ���� �׸� ������ �����Ѵ�.
	{
		// ���� - �ﰢ�� 
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(7);

	}


	// 3. matrix initialize
	{
		m_matWorld = cMatrix::Identity(4);
		m_matView = cMatrix::Identity(4);
		m_matProj = cMatrix::Identity(4);
		m_matViewport = cMatrix::Identity(4);
	}

	SetGrid();
}

void cMainGame::Update()
{
	
	// �ش� Ű�� ���������� �� ����
	if (GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY -= 0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 0.1f;
	}

	if (GetKeyState('R') & 0x8000)
	{
		cVector3 tmp;
		
		tmp.x = 0;
		tmp.y = 0;
		tmp.z = -5.0f;
		m_vEye = tmp;
		
		tmp.z = 0.0f;
		m_vLookAt = tmp;

		tmp.y = 1.0f;
		m_vUp = tmp;

		tmp.y = 0.0f;
		m_vPosition = tmp;
		
		m_fCameraDistance = 5.0f;
		m_isLButtonDown = false;
		m_vCamRotAngle = tmp;;
		m_fBoxRotY = 0.0f;

		tmp.z = 1.0f;
		m_vBoxDirection = tmp;		
		
		m_fScale = 1.0f;
	}

	// Scale, Rotate, Trans
	Update_Move();
	Update_Scale();


	//ī�޶� ���� ȸ�� ��Ʈ����
	GetClientArea(g_hWnd);

	cMatrix matRX = cMatrix::RotationX(m_vCamRotAngle.x);
	cMatrix matRY = cMatrix::RotationY(m_vCamRotAngle.y);
	cMatrix matR = matRX * matRY;

	m_vEye = cVector3(0, m_fCameraDistance, -m_fCameraDistance);

	m_vEye = cVector3::TransformCoord(m_vEye, matR);

	m_vLookAt = m_vPosition;
	m_vEye = m_vEye + m_vPosition;

	//�ڽſ� ���� ȸ�� ��Ʈ����
	matR = cMatrix::RotationY(m_fBoxRotY);

	cMatrix matS = cMatrix::Scale(m_fScale);
	matR = matS * matR;

	m_vBoxDirection = cVector3(0, 0, 1);
	m_vBoxDirection = cVector3::TransformNormal(m_vBoxDirection, matR);

	//���� ��Ʈ����
	m_matWorld = matR * cMatrix::Translation(m_vPosition);

	//�� ��Ʈ����
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 4.0f, (double)(ClientRect.right / ClientRect.bottom), 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, ClientRect.right, ClientRect.bottom, 0, 1);

}

void cMainGame::Render(HDC hdc)
{
	HDC BackDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, ClientRect.right, ClientRect.bottom);
	SelectObject(BackDC, m_hBitmap);
	SelectObject(BackDC, GetStockObject(NULL_PEN));
	Rectangle(BackDC, 0, 0, ClientRect.right, ClientRect.bottom);

	SelectObject(BackDC, GetStockObject(BLACK_PEN));


	cMatrix matWVP = m_matWorld * m_matView * m_matProj;

	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		// Backface Culling
		if (isBackface(v1, v2, v3))
			continue;

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		// �ﰢ�� �׸���
		MoveToEx(BackDC, v1.x, v1.y, NULL);
		LineTo(BackDC, v2.x, v2.y);
		LineTo(BackDC, v3.x, v3.y);
		LineTo(BackDC, v1.x, v1.y);
	}

	//�׸��� �׸���
	DrawGrid(BackDC);

	BitBlt(hdc, 0, 0, ClientRect.right, ClientRect.bottom, BackDC, 0, 0, SRCCOPY);

	SelectObject(BackDC, m_hBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(BackDC);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		break;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;
	case WM_MOUSEMOVE:
		if (m_isLButtonDown)
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);

			double fDeltaX = (double)ptCurMouse.x - m_ptPrevMouse.x;
			double fDeltaY = (double)ptCurMouse.y - m_ptPrevMouse.y;

			// x �� �̵��� (ȭ�� ��ǥ�� �¿�) -> 3D ��ǥ���� Y�� �̵��ӿ� ����
			// 1:1 ���� ��Ű�� ȸ�� ���� �ſ� Ŀ���Ƿ�, ���� ������ �����ش�.
			m_vCamRotAngle.y += (fDeltaX / 100.f);
			m_vCamRotAngle.x += (fDeltaY / 100.f);

			m_ptPrevMouse = ptCurMouse;
		}
		break;
	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);

		if (m_fCameraDistance < EPSILON)
			m_fCameraDistance = EPSILON;

		break;
	}
}

void cMainGame::SetGrid()
{
	// �׸��� ǥ�ÿ�
	int nNumHalfTile = 5;
	double fInterval = 1.0f;
	double fMax = nNumHalfTile * fInterval;
	double fMin = -nNumHalfTile * fInterval;

	for (int i = 1; i <= nNumHalfTile; i++)
	{
		m_vecGridVertex.push_back(cVector3(fMin, 0, i * fInterval));
		m_vecGridVertex.push_back(cVector3(fMax, 0, i * fInterval));
		m_vecGridVertex.push_back(cVector3(fMin, 0, -i * fInterval));
		m_vecGridVertex.push_back(cVector3(fMax, 0, -i * fInterval));

		m_vecGridVertex.push_back(cVector3(i * fInterval, 0, fMin));
		m_vecGridVertex.push_back(cVector3(i * fInterval, 0, fMax));
		m_vecGridVertex.push_back(cVector3(-i * fInterval, 0, fMin));
		m_vecGridVertex.push_back(cVector3(-i * fInterval, 0, fMax));
	}

	//��� ���� ����ְ� �Ǵϱ� ä���ش�.
	m_vecGridVertex.push_back(cVector3(0, 0, fMin));
	m_vecGridVertex.push_back(cVector3(0, 0, fMax));

	m_vecGridVertex.push_back(cVector3(fMin, 0, 0));
	m_vecGridVertex.push_back(cVector3(fMax, 0, 0));
	
	m_vAxisXTextPos = cVector3(fMax, 0, 0);
	m_vAxisZTextPos = cVector3(0, 0, fMax);
}

void cMainGame::DrawGrid(HDC BackDC)
{
	cMatrix mat = m_matView * m_matProj * m_matViewport;

	for (size_t i = 0; i < m_vecGridVertex.size(); i += 2)
	{
		cVector3 v1 = m_vecGridVertex[i + 0];
		cVector3 v2 = m_vecGridVertex[i + 1];

		v1 = cVector3::TransformCoord(v1, mat);
		v2 = cVector3::TransformCoord(v2, mat);

		MoveToEx(BackDC, v1.x, v1.y, NULL);
		LineTo(BackDC, v2.x, v2.y);
	}


	{
		cVector3 tmpX = m_vAxisXTextPos;
		tmpX = cVector3::TransformCoord(tmpX, mat);
		TextOut(BackDC, tmpX.x, tmpX.y, _T("X"), 1);

		cVector3 tmpY = m_vAxisZTextPos;
		tmpY = cVector3::TransformCoord(tmpY, mat);
		TextOut(BackDC, tmpY.x, tmpY.y, _T("Z"), 1);
	}
}

bool cMainGame::isBackface(cVector3 StartPoint, cVector3 MiddlePoint, cVector3 EndPoint)
{
	/*
	�׸����� ���� ù��° �ﰢ���� �� 3���� ������ ���� ���͸� ���Ѵ�.
	�߰��� -> ������ ���Ϳ� �߰��� -> ���� ������ CROSS PRODUCT = ���� ����
	���� ���Ϳ� ���� �ٶ󺸴� ���� (m_vEye ����)�� ����(Dot Product)�� 0 �̻��̸� ���� �Ǵ� ���� -> ���̴� ��
	0 �̸��̸� �а� -> �Ⱥ��̴� ��.
	(������ ������ 0 <= Theta <= PI �̹Ƿ� 180�� ���� ������ �־�����. (���� ����)
	�ڻ��� ��� ���� 0�� ~ 90���� �� 1 ~ 0����.
	90�� �ʰ� ~ 180�� ���� 0 ~ -1�� ���Ѵ�.
	�ٽ� ���ؼ�, �� ���Ͱ� �̷�� ���� cos(Theta)���� �������̸� �а� = ������ �ʴ� ��.

	*/

	/*
	//cVector3 v1 = StartPoint - MiddlePoint;
	//cVector3 v2 = EndPoint - MiddlePoint;
	cVector3 normal = cVector3::Cross(StartPoint - MiddlePoint, EndPoint - MiddlePoint);

	// �� ������ DOT PRODUCT���� 0�̸� ����, 0 �̸��̸� ����, 0�ʰ��� �а�
	// �Ǽ� ����̹Ƿ� ������ EPSILON�� ������� �Ѵ�.
	if (cVector3::Dot(normal, m_vLookAt - m_vEye) < EPSILON)
	return false;
	else
	return true;

	*/
	cVector3 v1 = MiddlePoint - StartPoint;
	cVector3 v2 = EndPoint - StartPoint;


	cVector3 n = cVector3::Cross(v1, v2);

	if (cVector3::Dot(n, cVector3(0, 0, 1)) > 0)
		return true;
	else
		return false;

}

void cMainGame::Update_Move()
{


	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + (m_vBoxDirection * 0.1f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - (m_vBoxDirection * 0.1f);
	}
}



void cMainGame::Update_Scale()
{

	if (GetKeyState('Z') & 0x8000)
	{
		m_fScale += 0.1f;
		if (m_fScale > 2.0f)
			m_fScale = 2.0f;
	}

	if (GetKeyState('X') & 0x8000)
	{

		m_fScale -= 0.1f;
		if (m_fScale < 0.2f)
			m_fScale = 0.2f;
	}


}




double cMainGame::GetRotationX()
{
	return myRotationX;
}

double cMainGame::GetRotationY()
{
	return myRotationY;
}

double cMainGame::GetRotationZ()
{
	return myRotationZ;
}

cVector3 cMainGame::GetTransformXYZ()
{
	cVector3 ret;

	ret.x = myTransformX;
	ret.y = myTransformY;
	ret.z = myTransformZ;

	return ret;
}


cVector3 cMainGame::GetMyScaleVector()
{
	cVector3 ret;
	ret.x = myScaleX;
	ret.y = myScaleY;
	ret.z = myScaleZ;

	return ret;
}

void cMainGame::SetMyScale(double scale_x, double scale_y, double scale_z)
{
	if (scale_x > 2.0f + EPSILON)
		myScaleX = 2.0f;
	else if (scale_x < 0.2f + EPSILON)
		myScaleX = 0.2f;
	else
		myScaleX = scale_x;


	if (scale_y > 2.0f + EPSILON)
		myScaleY = 2.0f;
	else if (scale_y < 0.2f + EPSILON)
		myScaleY = 0.2f;
	else
		myScaleY = scale_y;

	if (scale_z > 2.0f + EPSILON)
		myScaleZ = 2.0f;
	else if (scale_z < 0.2f + EPSILON)
		myScaleZ = 0.2f;
	else
		myScaleZ = scale_z;

}

void cMainGame::SetMyScale(cVector3 scaleVector)
{
	if (scaleVector.x > 2.0f + EPSILON)
		myScaleX = 2.0f;
	else if (scaleVector.x < 0.2f + EPSILON)
		myScaleX = 0.2f;
	else
		myScaleX = scaleVector.x;


	if (scaleVector.y > 2.0f + EPSILON)
		myScaleY = 2.0f;
	else if (scaleVector.y < 0.2f + EPSILON)
		myScaleY = 0.2f;
	else
		myScaleY = scaleVector.y;

	if (scaleVector.z > 2.0f + EPSILON)
		myScaleZ = 2.0f;
	else if (scaleVector.z < 0.2f + EPSILON)
		myScaleZ = 0.2f;
	else
		myScaleZ = scaleVector.z;
}

void cMainGame::GetClientArea(HWND hWnd)
{
	GetClientRect(hWnd, &ClientRect);
}



void cMainGame::SetRotationX(double fDegree)
{
	myRotationX = fDegree;
}

void cMainGame::SetRotationY(double fDegree)
{
	myRotationY = fDegree;
}

void cMainGame::SetRotationZ(double fDegree)
{
	myRotationZ = fDegree;
}

void cMainGame::SetTransformXYZ(double x, double y, double z)
{
	myTransformX = x;
	myTransformY = y;
	myTransformZ = z;

}

void cMainGame::SetTransformXYZ(cVector3 XYZ)
{
	myTransformX = XYZ.x;
	myTransformY = XYZ.y;
	myTransformZ = XYZ.z;

}