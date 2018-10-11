#pragma once

class cASELoader
{
public:
	cASELoader();
	~cASELoader();

	static vector<ASE_Obj> ParseASE(string FileName);
	 

};

