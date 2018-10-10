#pragma once


class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	static vector<SubMesh> ParseObj();
	static D3DMATERIAL9 GetMaterial(string filename, string MatName, SubMesh *Dest);
	static LPDIRECT3DTEXTURE9 GetTexture(string TextureName);
	
private:	
};