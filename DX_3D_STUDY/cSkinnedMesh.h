#pragma once
#define BLENDING_START_PLAY_RATE 0.85f
struct ST_BONE;

class cSkinnedMesh
{
public:
	cSkinnedMesh();	
	cSkinnedMesh(char* szFolder, char* szFilename);		// OBB 충돌을 위해 추가 2018-10-26
	~cSkinnedMesh();

protected:
	LPD3DXFRAME		m_pRoot;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;

	float	m_fBlendTime;
	float	m_fPassedBlendTime;
	bool	m_isAnimBlend;

public:
	void Setup(char* szFolder, char* szFile);	
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetAnimationIndex(int nIndex);
	int SetAnimationIndexBlend(int nIndex);
	float GetCurAnimPosRate();


	void Load(char* szFolder, char* szFilename);				// OBB 충돌을 위해 추가 2018-10-26
	void Destroy();												// OBB 충돌을 위해 추가 2018-10-26
	void UpdateAndRender();										// OBB 충돌을 위해 추가 2018-10-26
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);	// OBB 충돌을 위해 추가 2018-10-26
	void SetRandomTrackPosition();			// OBB 충돌을 위해 추가 2018-10-26
	void SetTransform(D3DXMATRIXA16 *pmat);

private:
	LPD3DXANIMATIONSET		m_pPrevAnimSet;
	LPD3DXANIMATIONSET		m_pNextAnimSet;
	float					m_fCurAnimPosRate;
	SYNTHESIZE(D3DXVECTOR3, m_vMin, Min);		// OBB 충돌을 위해 추가 2018-10-26
	SYNTHESIZE(D3DXVECTOR3, m_vMax, Max);		// OBB 충돌을 위해 추가 2018-10-26
	D3DXMATRIXA16			m_matWorldTM;

		


};

