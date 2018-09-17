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
	myScaleX = scale_x;
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
	// ������ ��ǥ�� ���Ѵ�
	{
		// ���� -> �»� -> ��� -> ����
		// ����
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));

		// ���
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

		// ��� - �ﰢ��
		// ����� �������� ������ �� �ð����
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(5);
		
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(6);

		// ���� - ������ ����
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(1);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(0);

		// ���� - ������ ������
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(3);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(7);

		// �Ѳ�
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(2);


		// �ٴ�
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(7);

	}


	// �׸��� ǥ�ÿ�
	{
		for (double i = -10.0f; i <= 10.0f; i+=1.0f)
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

	// X�࿡ ������ �׸��� �׸���� ���� ���� vector
	m_vecGrid_X_ToDraw.clear();
	for (int i = 0; i < m_vecGrid_X.size(); i++)
	{
		cVector3 vTemp;
		vTemp = cVector3::TransformCoord(m_vecGrid_X[i], m_matView);
		vTemp = cVector3::TransformCoord(vTemp, m_matProj);
		vTemp = cVector3::TransformCoord(vTemp, m_matViewport);
		m_vecGrid_X_ToDraw.push_back(vTemp);
	}

	// Z �࿡ ������ �׸��� �׸���� ���� ���� vector
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
	

	
	// �׸��� �׸���
	for (int i = 0; i < m_vecGrid_X_ToDraw.size(); i += 2)
	{
		// X�࿡ ������ �� �׸���
		MoveToEx(BackDC, m_vecGrid_X_ToDraw[i].x, m_vecGrid_X_ToDraw[i].y, NULL);
		LineTo(BackDC, m_vecGrid_X_ToDraw[i+1].x, m_vecGrid_X_ToDraw[i+1].y);

		
		// Z�࿡ ������ �� �׸���
		MoveToEx(BackDC, m_vecGrid_Z_ToDraw[i].x, m_vecGrid_Z_ToDraw[i].y, NULL);
		LineTo(BackDC, m_vecGrid_Z_ToDraw[i+1].x, m_vecGrid_Z_ToDraw[i+1].y);
	}


	GetStockObject(WHITE_PEN);
	// ����ü �׸���
	//for (int i = 0; i < m_vecIndex.size() - 1; i+=3)
		for (int i = 0; i <  m_vecIndex.size() - 1; i += 3)
	{
		MoveToEx(BackDC, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y, NULL);
		printf("Moveto #%d (%f,%f)\n", i, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y);
		LineTo(BackDC, m_vecVertexToDraw[m_vecIndex[i+1]].x, m_vecVertexToDraw[m_vecIndex[i+1]].y);
		LineTo(BackDC, m_vecVertexToDraw[m_vecIndex[i+2]].x, m_vecVertexToDraw[m_vecIndex[i+2]].y);
		LineTo(BackDC, m_vecVertexToDraw[m_vecIndex[i]].x, m_vecVertexToDraw[m_vecIndex[i]].y);
	}	



	BitBlt(hdc, 0, 0, ClientRect.right, ClientRect.bottom, BackDC, 0, 0, SRCCOPY);

	DeleteObject(m_hBitmap);
	DeleteDC(BackDC);

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	

}
