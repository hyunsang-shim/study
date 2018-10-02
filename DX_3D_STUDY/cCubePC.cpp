#include "stdafx.h"

class cCamera;
cCubePC::cCubePC()
	:m_vBoxDirection(0, 0, 1)
	, m_vBoxPosition(0, 0, 10)
	, m_fBoxScale(1.0f)
	, m_fBoxRotY(0.1f)
	, m_pTexture(NULL)
{	 
	D3DXMatrixIdentity(&m_matWorld);
}


cCubePC::~cCubePC()
{
	SAFE_DELETE(m_pTexture);
}

void cCubePC::Setup()
{
	ST_PNT_VERTEX	v;
	D3DXCreateTextureFromFile(g_pD3DDevice, _T(".\\obj\\box.jpg"), &m_pTexture);
	m_vecVertex = ObjLoader::ParseObj(".\\obj\\box.obj");
	MATERIAL tmp;
	tmp = ObjLoader::GetMaterial(".\\obj\\box.mtl");

	m_material.Ambient = D3DXCOLOR(tmp.Ambient.r, tmp.Ambient.g, tmp.Ambient.b, 1.0f);
	m_material.Diffuse = D3DXCOLOR(tmp.Diffuse.r, tmp.Diffuse.g, tmp.Diffuse.b, 1.0f);
	m_material.Specular = D3DXCOLOR(tmp.Specular.r, tmp.Specular.g, tmp.Specular.b, 1.0f);
	m_material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_material.Power = tmp.Power;
	/*
	vecVerTex_Box.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));	vecVerTex_Box.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	vecVerTex_Box.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));	vecVerTex_Box.push_back(D3DXVECTOR3(1.0f, -1.0f, -1.0f));

	vecVerTex_Box.push_back(D3DXVECTOR3(-1.0f, -1.0f, 1.0f));	vecVerTex_Box.push_back(D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	vecVerTex_Box.push_back(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	vecVerTex_Box.push_back(D3DXVECTOR3(1.0f, -1.0f, 1.0f));

	vecVerTex_Box_Index.push_back(0);	vecVerTex_Box_Index.push_back(1);	vecVerTex_Box_Index.push_back(2);
	vecVerTex_Box_Index.push_back(0);	vecVerTex_Box_Index.push_back(2);	vecVerTex_Box_Index.push_back(3);
	
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(6);	vecVerTex_Box_Index.push_back(5);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(7);	vecVerTex_Box_Index.push_back(6);
	
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(5);	vecVerTex_Box_Index.push_back(1);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(1);	vecVerTex_Box_Index.push_back(0);
	
	vecVerTex_Box_Index.push_back(3);	vecVerTex_Box_Index.push_back(2);	vecVerTex_Box_Index.push_back(6);
	vecVerTex_Box_Index.push_back(3);	vecVerTex_Box_Index.push_back(6);	vecVerTex_Box_Index.push_back(7);
	
	vecVerTex_Box_Index.push_back(1);	vecVerTex_Box_Index.push_back(5);	vecVerTex_Box_Index.push_back(6);
	vecVerTex_Box_Index.push_back(1);	vecVerTex_Box_Index.push_back(6);	vecVerTex_Box_Index.push_back(2);
	
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(0);	vecVerTex_Box_Index.push_back(3);
	vecVerTex_Box_Index.push_back(4);	vecVerTex_Box_Index.push_back(3);	vecVerTex_Box_Index.push_back(7);
	
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y2));		vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x2, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y2));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x2, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(x2, y2));
	
	vecVerTex_Texture.push_back(D3DXVECTOR2(x3, y2));		vecVerTex_Texture.push_back(D3DXVECTOR2(x4, y1));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x3, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(x3, y2));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x4, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(x4, y1));

	vecVerTex_Texture.push_back(D3DXVECTOR2(0, y2));		vecVerTex_Texture.push_back(D3DXVECTOR2(0, y1));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(0, y2));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y2));

	vecVerTex_Texture.push_back(D3DXVECTOR2(0, y2));		vecVerTex_Texture.push_back(D3DXVECTOR2(0, y1));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(0, y2));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y2));

	vecVerTex_Texture.push_back(D3DXVECTOR2(0, y2));		vecVerTex_Texture.push_back(D3DXVECTOR2(0, y1));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(0, y2));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y2));

	vecVerTex_Texture.push_back(D3DXVECTOR2(0, y2));		vecVerTex_Texture.push_back(D3DXVECTOR2(0, y1));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(0, y2));
	vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y1));		vecVerTex_Texture.push_back(D3DXVECTOR2(x1, y2));
	
	

	for (int i = 0; i < vecVerTex_Box_Index.size(); i++)
	{
		v.p = vecVerTex_Box[vecVerTex_Box_Index[i]];
		v.texture = vecVerTex_Texture[vecVerTex_Box_Index[i]];
		m_vecVertex.push_back(v);
	}
	*/
}

void cCubePC::Update()
{
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixScaling(&m_matScale, m_fBoxScale, m_fBoxScale, m_fBoxScale);
	D3DXMatrixRotationY(&m_matRotY, m_fBoxRotY);	
	D3DXMatrixTranslation(&m_matTrans, m_vBoxPosition.x, m_vBoxPosition.y, m_vBoxPosition.z);
	m_matWorld = m_matScale * m_matRotY * m_matTrans;
}

void cCubePC::Render()
{

	g_pD3DDevice->SetTexture(0, m_pTexture);	// 텍스쳐 사용 선언
	g_pD3DDevice->SetMaterial(&m_material);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PNT_VERTEX));

	g_pD3DDevice->SetTexture(0, NULL);	// 텍스쳐 사용 하지 않음 선언

}

void cCubePC::SetBoxPosition(D3DXVECTOR3 boxPos)
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	 m_vBoxPosition = boxPos;
}

void cCubePC::SetBoxScale(double scale)
{
	m_fBoxScale = scale;
}

void cCubePC::SetBoxRotationY(double rotation)
{
	m_fBoxRotY = rotation;
}

vector<D3DXVECTOR3> cCubePC::GetOriginVertexList()
{
	return vecVerTex_Box;
}
