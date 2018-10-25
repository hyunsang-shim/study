#pragma once
#define BLENDING_START_RATE 0.85f

class cSkinnedMesh
{
public:
	cSkinnedMesh();
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
	void Update(LPD3DXFRAME pFrame,
		LPD3DXFRAME pParent);

	void Render(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);
	int SetAnimationIndexBlend(int nIndex);

	float GetCurAnimPosRate();

private:
	LPD3DXANIMATIONSET	m_pPrevAnimSet;
	LPD3DXANIMATIONSET	m_pNextAnimSet;
	float				m_fCurAnimPosRate;

		


};

