#include "stdafx.h"
#include "cASE_Char.h"


cASE_Char::cASE_Char()
{
}


cASE_Char::~cASE_Char()
{
}

void cASE_Char::Setup()
{
	string FileName = "./woman/woman_01_all.ASE";
	ASEOBJ = cASELoader::ParseASE(FileName);

}

void cASE_Char::Update()
{
}

void cASE_Char::Render()
{
}
