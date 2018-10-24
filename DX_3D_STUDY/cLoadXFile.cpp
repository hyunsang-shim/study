#include "stdafx.h"
#include "cLoadXFile.h"


cLoadXFile::cLoadXFile()
	: msh_Mesh(NULL)
	, vMaterials(NULL)
	, vTextures(NULL)
{
}


cLoadXFile::~cLoadXFile()
{
}

void cLoadXFile::Setup(string filepath)
{	
	HRESULT						hr = 0;
	ID3DXBuffer*		adjBuffer = 0;
	ID3DXBuffer*		mtlBuffer = 0;
	DWORD numMtls = 0;

	hr = D3DXLoadMeshFromXA("Xfile/bigshipl.x",
		D3DXMESH_MANAGED, g_pD3DDevice,
		&adjBuffer, &mtlBuffer,
		0, &numMtls,
		&msh_Mesh );
		
	if (mtlBuffer != 0 && numMtls != 0)
	{
		D3DXMATERIAL* v_Mtl = (D3DXMATERIAL*)mtlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtls; i++)
		{
			v_Mtl[i].MatD3D.Ambient = v_Mtl[i].MatD3D.Diffuse;

			vMaterials.push_back(v_Mtl[i].MatD3D);

			if (v_Mtl[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(g_pD3DDevice, v_Mtl[i].pTextureFilename, &tex);

				vTextures.push_back(tex);
			}
			else
			{
				vTextures.push_back(0);
			}
		}
	}

	SAFE_RELEASE(mtlBuffer);
	
}

void cLoadXFile::Update()
{
}

void cLoadXFile::Render()
{
	static float y = 0.0f;
	D3DXMATRIX yRot;
	D3DXMatrixRotationY(&yRot, y);
	y += g_pTimeManager->GetElapsedTime();

	if (y >= 6.28f)
		y = 0.0f;

	D3DXMATRIX matWorld= yRot;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (int i = 0; i < vMaterials.size(); i++)
	{
		g_pD3DDevice->SetMaterial(&vMaterials[i]);
		g_pD3DDevice->SetTexture(0, vTextures[i]);
		msh_Mesh->DrawSubset(i);
	}
}
