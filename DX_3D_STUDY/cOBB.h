#pragma once

class cSkinnedMesh;
class cOBB
{
public:
	cOBB();
	~cOBB();

	void Setup(cSkinnedMesh* pSkinnedMesh);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(cOBB* pOBB1, cOBB* pOBB2);
	void OBBBox_Render(D3DCOLOR c);

private:
	D3DXVECTOR3		m_vOrgCenterPos;
	D3DXVECTOR3		m_vOrgAxisDir[3];
	D3DXVECTOR3		m_vCenterPos;
	D3DXVECTOR3		m_vAxisDir[3];
	float			m_fAxisLength[3];
	float			m_fAxisLength_Half[3];

	D3DXMATRIXA16	m_matWorldTM;
	LPDIRECT3DVERTEXBUFFER9			m_VB;
	vector<WORD>					m_nIB_SubMesh;
};

