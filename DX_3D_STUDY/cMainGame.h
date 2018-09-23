#pragma once

class cCubePC;
class cBoxman;
class cCamera;
class cGrid;
class cCubeman;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();
	
private:
	D3DXVECTOR3					 m_vEye;
	D3DXVECTOR3					 m_vLookAt;
	D3DXVECTOR3					 m_vUp;
	D3DXVECTOR3					 m_vBoxPosition;
	D3DXVECTOR3					 m_vfront;

	POINT						m_ptPrevMouse;
	bool						m_isLButtonDown;
	bool						m_isMButtonDown;
	double						m_fCameraDistance;

	D3DXVECTOR3					m_vCamRotAngle;
	double						m_fCamTransY;
	D3DXVECTOR3					m_vAxisXTextPos;
	D3DXVECTOR3					m_vAxisZTextPos;

	double						m_fBoxRotY;
	double						m_fBoxScale;

	D3DXVECTOR3					m_vBoxDirection = { 0,0,1 };

public:
	void						Setup();
	void						Update();
	void						Render();

	bool						isMoving;
	bool						isRotating;
	bool						swing;

	void						WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	cCubePC*					m_pCubePC;
	cCamera*					m_pCamera;	
	cCubeman*					m_pCubeman;
	LPDIRECT3DTEXTURE9			m_pTexture;
	vector<ST_PT_VERTEX>		m_vecVertex;
	cGrid*						m_pGrid;
	cBoxman*					m_pBoxman;
	vector<D3DXVECTOR3>			m_vecOriginalBox;



};

