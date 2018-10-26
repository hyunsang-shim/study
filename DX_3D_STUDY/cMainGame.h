#pragma once

class cCubePC;
class cBoxman;
class cCamera;
class cGrid;
class cCubeman;
class cMap;
class cASE_Char;
class cHeightMap;
class cLoadXFile;
class cFrustumCulling;


// 강사님st
class cFrame;
class cSkinnedMesh;
class cZealot;



typedef struct besiertrail_boxman {
	bool						m_isMoving;
	bool						m_isRunning;
	double						m_fBoxRotY;
	D3DXVECTOR3					m_vBoxDirection = { 0,0,1 };
	D3DXVECTOR3					m_vBoxPosition;
	cBoxman*					boxman;
}BESIER_BOXMAN;



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
	void						Mesh_Render();
	void						Mesh_Setup();

	void						InitMaterial();
	void						InitLights();

	bool						m_isMoving;
	bool						m_isRunning;
	bool						m_isRotating;
	bool						m_isJumping;	
	bool						m_isJumping_Top;


	bool						m_swDirLight;
	bool						m_swSpotLight;

	void						WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	cCubePC*					m_pCubePC;
	cMap*						m_pMap;
	cCamera*					m_pCamera;	
	cCubeman*					m_pCubeman;
	cBoxman*					m_pBoxman;
	LPDIRECT3DTEXTURE9			m_pTexture;
	vector<ST_PT_VERTEX>		m_vecVertex;
	cGrid*						m_pGrid;
	cASE_Char*					m_pASE_Char;
	cHeightMap*					m_pHeightmap;
	vector<BESIER_BOXMAN>		m_vecNormalBoxman;			// 일반 경로를 따라 가는 캐릭터 구조체 저장소
	vector<BESIER_BOXMAN>		m_vecBesierBoxman;			// 베지어 곡선 경로를 따라 가는 캐릭터 구조체 저장소
	vector<D3DXVECTOR3>			m_vecOriginalBox;
	bool						m_isCamFollow;				// 카메라를 따라가게 할 것인지에 대한 플래그 값.
	cHexagon*					m_pHexagon;
	cLoadXFile*					m_pLoadFromX;
	vector<D3DXVECTOR3>			m_vWaypoints;
	cFrustumCulling*			m_pFrustum;

	LPD3DXMESH					m_pMeshTeapot;			 	// 메시 렌더링 예제
	D3DMATERIAL9				m_stMrlTeapot;				// 메시 렌더링 예제
	cSkinnedMesh*				m_pSkinnedMesh;
	
	IDirect3DTexture9*			m_pTextures;


	cZealot*					m_pHoldZealot;
	cZealot*					m_pMoveZealot;

	

	// 강사님 ASE 로더
	cFrame*						m_pRootFrame;


};

