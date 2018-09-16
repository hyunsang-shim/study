#include "stdafx.h"
#include "cMainGame.h"
#include "cMatrix.h"

cMainGame::cMainGame()
	:m_hBitmap(NULL), m_vEye(0, 0, -5), m_vLookAt(0, 0, 0), m_vUp(0, 1, 0), m_vPosition(0, 0, 0)
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

cVector3 cMainGame::GetMyScaleVector()
{
	return { myScaleX, myScaleY, myScaleZ };
}

void cMainGame::SetMyScale(double scale_x, double scale_y, double scale_z)
{
	myScaleX = scale_y;
	myScaleY = scale_y;
	myScaleZ = scale_z;

}

void cMainGame::SetMyScale(cVector3 scaleVector)
{
	myScaleX = scaleVector.x;
	myScaleY = scaleVector.y;
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
	m_matScale = cMatrix::Translation(myScaleX, myScaleY, myScaleZ);
	m_matRotation = cMatrix::Translation(myRotationX, myRotationY, myRotationZ);
	m_matTransform = cMatrix::Translation(myTransformX, myTransformY, myTransformZ);

	// World, View, Projectiopn, Viewport
	// x View -> x Projection -> x Viewport

	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 2.0f, 800 / 600, 1, 1000);
	m_matViewport = cMatrix::Viewport(0, 0, 800, 600, 0, 1);

	m_vecVertexToDraw.clear();
	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		cVector3 vTemp;
		vTemp = cVector3::TransformCoord(m_vecVertex[i], m_matScale);
		//vTemp = cVector3::TransformCoord(vTemp, m_matRotation);
		//vTemp = cVector3::TransformCoord(vTemp, m_matTransform);
		vTemp = cVector3::TransformCoord(vTemp, m_matView);
		//vTemp = cVector3::TransformCoord(m_vecVertex[i], m_matView);
		vTemp = cVector3::TransformCoord(vTemp, m_matProj);
		vTemp = cVector3::TransformCoord(vTemp, m_matViewport);		
		m_vecVertexToDraw.push_back(vTemp);
	}


}

void cMainGame::Render(HDC hdc)
{
	Update();
	// draw... lines	
	int cnt = 0;
	//for (int i = 0; i < m_vecIndex.size()-1; i++)
	for (int i = 0; i < m_vecIndex.size() - 1; i+=3)
	{
		MoveToEx(hdc, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y, NULL);		
		printf("Moveto #%d (%f,%f)\n", i, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y);
		LineTo(hdc, m_vecVertexToDraw[m_vecIndex[i+1]].x, m_vecVertexToDraw[m_vecIndex[i+1]].y);
		LineTo(hdc, m_vecVertexToDraw[m_vecIndex[i+2]].x, m_vecVertexToDraw[m_vecIndex[i+2]].y);
		LineTo(hdc, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y);
	}	
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	

}
