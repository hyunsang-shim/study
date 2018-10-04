#pragma once

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	static vector<OBJ_IMPORTER> ParseObj(char* FileName);
	static map<string, MATERIAL> GetMaterial(char* Filename);
	static LPDIRECT3DTEXTURE9 GetTexture(char* fileName);
private:

};

