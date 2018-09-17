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
	vector<cVector3>	m_vecGrid_X;
	vector<cVector3>	m_vecGrid_Z;
	vector<cVector3>	m_vecGrid_X_ToDraw;
	vector<cVector3>	m_vecGrid_Z_ToDraw;
			
	
	cMatrix m_matScale;
	cMatrix m_matRotation;
	cMatrix m_matTransform;
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
	bool isBackface(cVector3 StartPoint, cVector3 MiddlePoint, cVector3 EndPoint);

	cVector3 GetMyScaleVector();
	void SetMyScale(double x, double y, double z);
	void SetMyScale(cVector3 scaleVector);
	void GetClientArea(HWND hWnd);

private:
	double myRotationX = 0.0f;
	double myRotationY = 0.0f;
	double myRotationZ = 0.0f;
	double myTransformX = 0.0f;
	double myTransformY = 0.0f;
	double myTransformZ = 0.0f;
	double myScaleX = 1;
	double myScaleY = 1;
	double myScaleZ = 1;

	RECT ClientRect;
};

