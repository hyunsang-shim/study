#pragma once


class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	
	// struct SubMesh {	
	// string						sGroupName;
	// string						sMaterialName;
	// D3DMATERIAL9				mat9Material;
	// string						sTextureName;
	// LPDIRECT3DTEXTURE9			tx9Texture;
	// vector<ST_PNT_VERTEX>		vPNT_VERTEX;
	// enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };	
	// };
	static vector<SubMesh> ParseObj(string FileName);

	static D3DMATERIAL9 GetMaterial(string filename, string MatName, SubMesh *Dest);
	
private:	

};