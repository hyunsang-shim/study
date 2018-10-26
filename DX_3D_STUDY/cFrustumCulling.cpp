#include "stdafx.h"
#include "cFrustumCulling.h"


cFrustumCulling::cFrustumCulling()
	: m_frustum(6)
{
	m_sphereRadius = 1.0f;
}


cFrustumCulling::~cFrustumCulling()
{
}

void cFrustumCulling::Setup()
{
	m_frustum = UpdateFrustum();

	for (int i = -15; i < 15; i++)
	{
		for (int j = -15; j < 15; j++)
		{
			for (int k = -15; k < 15; k++)
			{
				Ball tmp;
				tmp.isInside = false;

				D3DXCreateSphere(g_pD3DDevice, 0.5f, 5, 5, &tmp.Sphere, NULL);
				ZeroMemory(&tmp.Material, sizeof(D3DMATERIAL9));
				tmp.Material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				tmp.Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				tmp.Material.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				tmp.Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				tmp.Material.Power = 8.0f;
				tmp.Pos = D3DXVECTOR3(i, j, k);

				D3DXMATRIXA16 matS, matR, matT;
				D3DXMatrixIdentity(&matS);
				D3DXMatrixIdentity(&matR);
				D3DXMatrixIdentity(&matT);
				D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
				D3DXMatrixTranslation(&matT, tmp.Pos.x + 0.5f, tmp.Pos.y + 0.5f, tmp.Pos.z + 0.5f);
				tmp.matWorld = matS* matR* matT;
								
				m_vBalls.push_back(tmp);
			}
		}
	}


	g_pD3DDevice->SetLight(0, &m_Light);
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light.Direction = D3DXVECTOR3(1, -1, 1);


}

void cFrustumCulling::Update(D3DXVECTOR3 eye)
{	

	m_frustum = UpdateFrustum();

	for (int i = 0; i < m_vBalls.size(); i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (D3DXPlaneDotCoord(&m_frustum[j], &m_vBalls[i].Pos) + 0.5f < 0)
			{
				m_vBalls[i].isInside = false;
				break;
			}
			else
				m_vBalls[i].isInside = true;
		}		
	}
	
}

void cFrustumCulling::Render()
{	
	//g_pD3DDevice->SetLight(0, &m_Light);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	for (int i = 0; i < m_vBalls.size(); i++)
	{
		if (m_vBalls[i].isInside)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vBalls[i].matWorld);
			//g_pD3DDevice->SetMaterial(&m_vBalls[i].Material);
			m_vBalls[i].Sphere->DrawSubset(0);
		}
	}

}

vector<D3DXPLANE> cFrustumCulling::UpdateFrustum()
{
	vector<D3DXPLANE>			tmp(6);
	D3DXMATRIX m_view;
	D3DXMATRIX m_projection;
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &m_projection);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &m_view);

	D3DXMatrixPerspectiveFovLH(&m_projection, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);



	D3DXMATRIX viewProjection;
	D3DXMatrixMultiply(&viewProjection, &m_view, &m_projection);

	// Left plane
	tmp[0].a = viewProjection._14 + viewProjection._11;
	tmp[0].b = viewProjection._24 + viewProjection._21;
	tmp[0].c = viewProjection._34 + viewProjection._31;
	tmp[0].d = viewProjection._44 + viewProjection._41;

	// Right plane
	tmp[1].a = viewProjection._14 - viewProjection._11;
	tmp[1].b = viewProjection._24 - viewProjection._21;
	tmp[1].c = viewProjection._34 - viewProjection._31;
	tmp[1].d = viewProjection._44 - viewProjection._41;

	// Top plane
	tmp[2].a = viewProjection._14 - viewProjection._12;
	tmp[2].b = viewProjection._24 - viewProjection._22;
	tmp[2].c = viewProjection._34 - viewProjection._32;
	tmp[2].d = viewProjection._44 - viewProjection._42;

	// Bottom plane
	tmp[3].a = viewProjection._14 + viewProjection._12;
	tmp[3].b = viewProjection._24 + viewProjection._22;
	tmp[3].c = viewProjection._34 + viewProjection._32;
	tmp[3].d = viewProjection._44 + viewProjection._42;

	// Near plane
	tmp[4].a = viewProjection._13;
	tmp[4].b = viewProjection._23;
	tmp[4].c = viewProjection._33;
	tmp[4].d = viewProjection._43;

	// Far plane
	tmp[5].a = viewProjection._14 - viewProjection._13;
	tmp[5].b = viewProjection._24 - viewProjection._23;
	tmp[5].c = viewProjection._34 - viewProjection._33;
	tmp[5].d = viewProjection._44 - viewProjection._43;

	// Normalize planes
	for (int i = 0; i < 6; i++)
	{
		D3DXPlaneNormalize(&tmp[i], &tmp[i]);
	}

	return tmp;
}
