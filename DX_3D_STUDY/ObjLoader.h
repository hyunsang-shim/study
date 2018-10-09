#pragma once

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	static vector<ST_PNT_SubMesh> ParseObj(string Filename);
	static map<string, MATERIAL> GetMaterialLib(string Filename);
	static map<string, string> GetTextures(map<string, MATERIAL> MaterialLibraryName);
	
private:

};