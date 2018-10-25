#pragma once


struct Ball {
	bool				isInside;
	LPD3DXMESH			Sphere;
	D3DMATERIAL9		Material;
	D3DXVECTOR3			Pos;
	D3DXMATRIXA16		matWorld;
};



class cFrustumCulling
{
public:
	cFrustumCulling();
	~cFrustumCulling();

	void	Setup();
	void	Update(D3DXVECTOR3 eye);
	void	Render();
	vector<D3DXPLANE>		UpdateFrustum();


private:
	vector<D3DXPLANE>		m_frustum;
	vector<D3DXVECTOR3>		m_vSpheres;
	vector<bool>			m_isInside;
	float					m_sphereRadius;
	vector<D3DXVECTOR3>		m_vecFrustumLines;
	LPD3DXMESH				m_MeshSphere;
	D3DMATERIAL9			m_stMtlSphere;				// 메시 렌더링 예제
	vector<Ball>			m_vBalls;
	D3DLIGHT9				m_Light;

};

