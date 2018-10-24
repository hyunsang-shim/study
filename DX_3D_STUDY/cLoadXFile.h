#pragma once
class cLoadXFile
{
public:
	cLoadXFile();
	~cLoadXFile();

	void Setup(string filepath);
	void Update();
	void Render();

private:
	ID3DXMesh*					msh_Mesh;
	vector<D3DMATERIAL9>		vMaterials;
	vector<IDirect3DTexture9*>	vTextures;
};

