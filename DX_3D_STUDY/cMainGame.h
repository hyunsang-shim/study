#pragma once

class cCubePC;
class cBoxman;
class cCamera;
class cGrid;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();
	
private:
	D3DXVECTOR3		 m_vEye;
	D3DXVECTOR3		 m_vLookAt;
	D3DXVECTOR3		 m_vUp;
	D3DXVECTOR3		 m_vBoxPosition;
	D3DXVECTOR3		 m_vfront;

	POINT			m_ptPrevMouse;
	bool			m_isLButtonDown;
	double			m_fCameraDistance;

	D3DXVECTOR3		m_vCamRotAngle;
	D3DXVECTOR3		m_vAxisXTextPos;
	D3DXVECTOR3		m_vAxisZTextPos;

	double			m_fBoxRotY;
	double			m_fBoxScale;

	D3DXVECTOR3		m_vBoxDirection = { 0,0,1 };

public:
	void			Setup();
	void			Update();
	void			Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	cCubePC*					m_pCubePC;
	cCamera*					m_pCamera;		
	cGrid*						m_pGrid;
	cBoxman*					m_pBoxman;
	vector<D3DXVECTOR3>			m_vecOriginalBox;

};

