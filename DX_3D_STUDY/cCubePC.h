#pragma once


class cCubePC
{
public:
	cCubePC();
	~cCubePC();

private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	vector<D3DXVECTOR3>		vecVerTex_Box;
	vector<int>				vecVerTex_Box_Index;
	D3DXMATRIXA16			m_matWorld;

	D3DXVECTOR3				m_vBoxDirection;
	D3DXVECTOR3				m_vBoxPosition;		// �ַ� ���ο��� �����Ѵ�.
	double					m_fBoxScale;			// ���ο��� �����Ѵ�.
	double					m_fBoxRotY;			// �ַ� ���ο��� �����Ѵ�.

public:
	void					Setup();
	void					Update();
	void					Render();
	void					SetBoxPosition(D3DXVECTOR3 box_pos);
	void					SetBoxScale(double scale);
	void					SetBoxRotationY(double rotY);
	
};

