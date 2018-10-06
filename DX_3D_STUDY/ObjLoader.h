#pragma once

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	static void ParseObj(string Filename);
	static void GetMaterialLib(string Filename);
	static void GetTextures(string Filename);
	
private:

};