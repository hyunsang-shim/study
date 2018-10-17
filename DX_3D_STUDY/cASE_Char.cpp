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
	//ASEOBJ = cASELoader::ParseASE(FileName);

}

void cASE_Char::Update()
{
	for (int i = 0; ASEOBJ.size(); i++)
	{
		if (ASEOBJ[i].parentNodeIdx != -1)
		{
			ASEOBJ[i].matMyWorld = ASEOBJ[ASEOBJ[i].parentNodeIdx].matMyWorld * ASEOBJ[i].matMyLocal;
		}
	}
}

void cASE_Char::Render()
{
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	for (int i = 0; i < ASEOBJ.size(); i++)
	{
		if (ASEOBJ[i].meshName == "ponytail")
		{
			if (ASEOBJ[i].mat9Material.Power < 0.0000001f)
			{
				g_pD3DDevice->SetTexture(0, ASEOBJ[i].tx9Texture);	// 텍스쳐 사용 하지 않음 선언
				g_pD3DDevice->SetMaterial(&ASEOBJ[i].mat9Material);
			}
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &ASEOBJ[i].matMyWorld);
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, ASEOBJ[i].vPNT_VERTEX.size() / 3, &ASEOBJ[i].vPNT_VERTEX[0], sizeof(ST_PC_VERTEX));
		}
	}
}
