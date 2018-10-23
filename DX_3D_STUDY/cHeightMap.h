#pragma once
class cHeightMap
{
public:
	cHeightMap();
	~cHeightMap();
	void Setup(string Filename);
	void Render();

private:
	ID3DXMesh*					m_pMesh;
	_D3DMATERIAL9				m_DefaultMaterial;
};

