#include "stdafx.h"
#include "cASELoader.h"


cASELoader::cASELoader()
{
}


cASELoader::~cASELoader()
{
}

vector<ASE_Obj> cASELoader::ParseASE(string FileName)
{

	ifstream					in;
	string						newline;
	char						indicator[128];
	vector<ASE_Obj>				ret;
	ASE_Obj						tmpRet;
	int							cntLines = 0;

	ZeroMemory(&ret, sizeof(ret));

	in.open("./woman/woman_01_all.ASE", ios::in);
	cntLines++;

	getline(in, newline);
	sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
	string tmp = indicator;

	if ( tmp == "*3DSMAX_ASCIIEXPORT")
	{
		while (cntLines < 15)
		{
			getline(in, newline);
			sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
			tmp = indicator;
			
			if (tmp == "*COMMENT") continue;

			printf("line #%02d Newline [%s] tmp [%s]\n", ++cntLines, newline.c_str(), tmp);

		}
	}

	return ret;
}


