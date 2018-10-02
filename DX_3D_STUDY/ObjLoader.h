#pragma once

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	static vector<ST_PNT_VERTEX> ParseObj(char* FileName);
	static MATERIAL GetMaterial(char* Filename);
private:

};

