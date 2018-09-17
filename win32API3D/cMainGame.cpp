#include "stdafx.h"
#include "cMainGame.h"
#include "cMatrix.h"

cMainGame::cMainGame()
	:m_hBitmap(NULL), m_vEye(0, 2, -5), m_vLookAt(0, 0, 0), m_vUp(0, 1, 0), m_vPosition(0, 0, 0)
{
}

cMainGame::~cMainGame()
{
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


bool cMainGame::isBackface(cVector3 StartPoint, cVector3 MiddlePoint, cVector3 EndPoint)
{
	/*
	그리려는 면의 첫번째 삼각형의 점 3개를 가지고 법선 벡터를 구한다.
	중간점 -> 시작점 벡터와 중간점 -> 끝점 벡터의 CROSS PRODUCT = 법선 벡터
	법선 벡터와 눈이 바라보는 방향 (m_vEye 벡터)의 내적(Dot Product)이 0 이상이면 직교 또는 예각 -> 보이는 면
	0 미만이면 둔각 -> 안보이는 면.
	(각도의 범위는 0 <= Theta <= PI 이므로 180도 범위 내에서 주어진다. (라디안 각도)
	코사인 곡선의 값은 0도 ~ 90도일 때 1 ~ 0으로.
	90도 초과 ~ 180도 까지 0 ~ -1로 변한다.
	다시 말해서, 두 벡터가 이루는 각의 cos(Theta)값이 음수값이면 둔각 = 보이지 않는 면.

	*/

	cVector3 v1 = StartPoint - MiddlePoint;
	cVector3 v2 = EndPoint - MiddlePoint;
	cVector3 normal = cVector3::Cross(v1, v2);

	// 두 벡터의 DOT PRODUCT값이 0이면 직교, 0 미만이면 예각, 0초과면 둔각
	// 실수 계산이므로 보정값 EPSILON을 대상으로 한다.
	if (cVector3::Dot(normal, m_vEye) < EPSILON)
		return false;
	else
		return true;



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

void cMainGame::Setup()
{
	// set...
	// 1. draw	




	// 2. Vertex
	// 정점의 좌표를 정한다
	{
		// 좌하 -> 좌상 -> 우상 -> 우하
		// 전면
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));

		// 배면
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));

	}

	// 선을 그릴 순서를 저장한다.
	{
		// 전면 - 삼각형 
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(0);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(3);

		// 배면 - 삼각형
		// 배면을 정면으로 보았을 때 시계방향
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(5);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(6);

		// 측면 - 정면의 왼쪽
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(1);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(0);

		// 측면 - 정면의 오른쪽
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(3);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(7);

		// 뚜껑
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(2);


		// 바닥
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(7);

	}


	// 그리드 표시용
	{
		for (double i = -10.0f; i <= 10.0f; i += 1.0f)
		{
			m_vecGrid_X.push_back(cVector3(-10.0f, 0.0f, i));
			m_vecGrid_X.push_back(cVector3(10.0f, 0.0f, i));
			m_vecGrid_Z.push_back(cVector3(i, 0.0f, -10.0f));
			m_vecGrid_Z.push_back(cVector3(-i, 0.0f, 10.0f));
		}
	}
	// 3. matrix initialize
	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);
}

void cMainGame::Update()
{


	// Scale, Rotate, Transform
	// Scale
	m_matScale = cMatrix::Scale(myScaleX, myScaleY, myScaleZ);
	m_matRotation = cMatrix::RotationY(myRotationY);
	m_matTransform = cMatrix::Translation(myTransformX, myTransformY, myTransformZ);

	// World, View, Projectiopn, Viewport
	// x View -> x Projection -> x Viewport

	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	//m_matProj = cMatrix::Projection(PI / 2.0f, 800 / 600, 1, 1000);
	m_matProj = cMatrix::Projection(PI / 2.0f, ClientRect.right / ClientRect.bottom, 1, 1000);
	m_matViewport = cMatrix::Viewport(0, 0, ClientRect.right, ClientRect.bottom, 0, 1);

	m_vecVertexToDraw.clear();
	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		cVector3 vTemp;
		vTemp = cVector3::TransformCoord(m_vecVertex[i], m_matScale);
		vTemp = cVector3::TransformCoord(vTemp, m_matRotation);
		vTemp = cVector3::TransformCoord(vTemp, m_matTransform);
		vTemp = cVector3::TransformCoord(vTemp, m_matView);
		//vTemp = cVector3::TransformCoord(m_vecVertex[i], m_matView);
		vTemp = cVector3::TransformCoord(vTemp, m_matProj);
		vTemp = cVector3::TransformCoord(vTemp, m_matViewport);
		m_vecVertexToDraw.push_back(vTemp);
	}

	// X축에 평행한 그리드 그리기용 정점 저장 vector
	m_vecGrid_X_ToDraw.clear();
	for (int i = 0; i < m_vecGrid_X.size(); i++)
	{
		cVector3 vTemp;
		vTemp = cVector3::TransformCoord(m_vecGrid_X[i], m_matView);
		vTemp = cVector3::TransformCoord(vTemp, m_matProj);
		vTemp = cVector3::TransformCoord(vTemp, m_matViewport);
		m_vecGrid_X_ToDraw.push_back(vTemp);
	}

	// Z 축에 평행한 그리드 그리기용 정점 저장 vector
	m_vecGrid_Z_ToDraw.clear();
	for (int i = 0; i < m_vecGrid_X.size(); i++)
	{
		cVector3 vTemp;
		vTemp = cVector3::TransformCoord(m_vecGrid_Z[i], m_matView);
		vTemp = cVector3::TransformCoord(vTemp, m_matProj);
		vTemp = cVector3::TransformCoord(vTemp, m_matViewport);
		m_vecGrid_Z_ToDraw.push_back(vTemp);
	}


}

void cMainGame::Render(HDC hdc)
{
	Update();
	// draw... lines	
	int cnt = 0;

	HDC BackDC = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, ClientRect.right, ClientRect.bottom);
	SelectObject(BackDC, m_hBitmap);
	Rectangle(BackDC, 0, 0, ClientRect.right, ClientRect.bottom);



	// 그리드 그리기
	for (int i = 0; i < m_vecGrid_X_ToDraw.size(); i += 2)
	{
		// X축에 평행한 선 그리기
		MoveToEx(BackDC, m_vecGrid_X_ToDraw[i].x, m_vecGrid_X_ToDraw[i].y, NULL);
		LineTo(BackDC, m_vecGrid_X_ToDraw[i + 1].x, m_vecGrid_X_ToDraw[i + 1].y);


		// Z축에 평행한 선 그리기
		MoveToEx(BackDC, m_vecGrid_Z_ToDraw[i].x, m_vecGrid_Z_ToDraw[i].y, NULL);
		LineTo(BackDC, m_vecGrid_Z_ToDraw[i + 1].x, m_vecGrid_Z_ToDraw[i + 1].y);
	}


	GetStockObject(WHITE_PEN);
	// 육면체 그리기
	//for (int i = 0; i < m_vecIndex.size() - 1; i+=3)
	for (int i = 0; i < m_vecIndex.size() - 1; i += 3)
	{
		
		if (!isBackface(m_vecVertexToDraw[m_vecIndex[i]], m_vecVertexToDraw[m_vecIndex[i + 1]], m_vecVertexToDraw[m_vecIndex[i + 2]]))
		{
			MoveToEx(BackDC, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y, NULL);
			printf("Moveto #%d (%f,%f)\n", i, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y);
			LineTo(BackDC, m_vecVertexToDraw[m_vecIndex[i + 1]].x, m_vecVertexToDraw[m_vecIndex[i + 1]].y);
			LineTo(BackDC, m_vecVertexToDraw[m_vecIndex[i + 2]].x, m_vecVertexToDraw[m_vecIndex[i + 2]].y);
			LineTo(BackDC, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y);
		}
	}



	BitBlt(hdc, 0, 0, ClientRect.right, ClientRect.bottom, BackDC, 0, 0, SRCCOPY);

	DeleteObject(m_hBitmap);
	DeleteDC(BackDC);

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}