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


	cMatrix m_matWorld;
	cMatrix m_matView;
	cMatrix m_matProj;
	cMatrix m_matViewport;


	cVector3 m_vEye;
	cVector3 m_vLookAt;
	cVector3 m_vUp;
	cVector3 m_vPosition;

public:
	void Setup();
	void Update();
	void Render(HDC);
	void WndProc(HWND hWNd, UINT message, WPARAM wParam, LPARAM lParam);
};

