#pragma once
#include "cVector3.h"
#include "cMatrix.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	HDC m_memDC;
	HBITMAP m_holdBitmap, m_hBitmap;

	//
	/*
	정점 관리용 변수
	*/

	vector<cVector3>	m_vecVertex;
	vector<DWORD>		m_vecIndex;
	vector<cVector3>	m_vecVertexToDraw;
			
	
	cMatrix m_matWorld;
	cMatrix m_matView;
	cMatrix m_matProj;
	cMatrix m_matViewport;
	cMatrix	m_matVPVp;


	cVector3 m_vEye;
	cVector3 m_vLookAt;
	cVector3 m_vUp;
	cVector3 m_vPosition;	

public:
	void Setup();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWNd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetRotationX(double fDegree);
	void SetRotationY(double fDegree);
	void SetRotationZ(double fDegree);
	void SetTransformXYZ(double x, double y, double z);

	double GetRotationX();
	double GetRotationY();
	double GetRotationZ();
	cVector3 GetTransformXYZ();


	double GetMyScale();
	void SetMyScale(double fScale);
	void GetClientArea(HWND hWnd);

private:
	double myRotationX = 1;
	double myRotationY = 1;
	double myRotationZ = 1;
	double myTransformX = 1;
	double myTransformY = 1;
	double myTransformZ = 1;
	double myScale = 0.5;
	RECT ClientRect;
};

