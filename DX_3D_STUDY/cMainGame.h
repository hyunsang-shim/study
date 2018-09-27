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
	vector<D3DXVECTOR3>			 m_vvecBoxPosition;
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


	ID3DXFont					*m_pFont;
	RECT						m_RectTxtArea;
	string						message;

	D3DLIGHT9					DirLight;
	D3DLIGHT9					DirLight_Default;
	D3DLIGHT9					SpotLight;
	D3DLIGHT9					PointLight;


	_D3DMATERIAL9				m_matWhite;
public:
	void						Setup();
	void						Update();
	void						Render();

	void						InitMaterial();
	void						InitLights();

	bool						m_isMoving;
	bool						m_isRunning;
	bool						m_isRotating;
	bool						m_isJumping;	
	bool						m_isJumping_Top;


	bool						m_swDirLight;

	void						WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	cCubePC*					m_pCubePC;
	cCamera*					m_pCamera;	
	cCubeman*					m_pCubeman;
	LPDIRECT3DTEXTURE9			m_pTexture;
	vector<ST_PT_VERTEX>		m_vecVertex;
	cGrid*						m_pGrid;
	vector<cBoxman*>			m_vpBoxman;	
	vector<D3DXVECTOR3>			m_vecOriginalBox;
	bool						m_isCamFollow;				// 카메라를 따라가게 할 것인지에 대한 플래그 값.
	cHexagon*					m_pHexagon;
	vector<D3DXVECTOR3>			m_vWaypoints;



};

