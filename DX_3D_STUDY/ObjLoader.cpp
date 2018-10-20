#include "stdafx.h"
#include "ObjLoader.h"

#define MAX_SIZE 1000

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

vector<SubMesh> ObjLoader::ParseObj(string filename)
{
	ifstream					in;
	string						newline;
	char						indicator[64];
	bool						isGroupStart = false;
	
	vector<SubMesh>				ret;		// 리턴 할 구조체 vector
	SubMesh						tmpSubMesh; // 리턴용에 push할 임시 구조체
	ST_PNT_VERTEX				tmpPNT;
	vector<D3DXVECTOR3>			vertex;
	vector<D3DXVECTOR3>			normal;
	vector<D3DXVECTOR2>			UV;

	string						path;
	string						fNameNoExt;
	size_t						found;
	size_t						found_dot;
	int							CntFaces = 0;
	int							CntUVFaces = 0;
	int							CntVertex = 0;
	int							CntNormal = 0;
	int							CntUV = 0;


	path = filename;

	found = path.find_last_of("/");
	if (found != path.npos)
		path.erase(found + 1);

	fNameNoExt = filename;

	fNameNoExt = filename.substr(found+1, filename.find_last_of(".") - path.length());
	in.open(filename, ios::in);

	while (!in.eof())
	{
		getline(in, newline);
		string tmp;
		sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
		tmp = indicator;


		if (tmp == "v")
		{
			float x, y, z;
			sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &y, &z);
			vertex.push_back(D3DXVECTOR3(x, y, z));
			
		}
		else if (tmp == "vt")
		{
			float u, v, w;
			sscanf_s(newline.c_str(), "%*s %f %f %*f", &u, &v);
			UV.push_back(D3DXVECTOR2(u, v));
		}
		else if (tmp == "vn")
		{
			float x, y, z;
			sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &y, &z);
			normal.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (tmp == "f")
		{
			
			int v1 = 0, v2 = 0, v3 = 0;
			int uv1 = 0, uv2 = 0, uv3 = 0;
			int vn1 = 0, vn2 = 0, vn3 = 0;

			sscanf(newline.c_str(),
				"%*s %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &uv1, &vn1, &v2, &uv2, &vn2, &v3, &uv3, &vn3);

			v1 -= CntVertex;
			v2 -= CntVertex;
			v3 -= CntVertex;

			uv1 -= CntUV;
			uv2 -= CntUV;
			uv3 -= CntUV;

			vn1 -= CntNormal;
			vn2 -= CntNormal;
			vn3 -= CntNormal;

			tmpPNT.p = D3DXVECTOR3(vertex[v1 - 1].x, vertex[v1 - 1].y, vertex[v1 - 1].z);			
			tmpPNT.normal = D3DXVECTOR3(normal[vn1 - 1].x, normal[vn1 - 1].y, normal[vn1 - 1].z);
			tmpPNT.texture = D3DXVECTOR2(UV[uv1 - 1].x, UV[uv1 - 1].y);
			tmpSubMesh.vPNT_VERTEX.push_back(tmpPNT);

			tmpPNT.p = D3DXVECTOR3(vertex[v2 - 1].x, vertex[v2 - 1].y, vertex[v2 - 1].z);
			tmpPNT.normal = D3DXVECTOR3(normal[vn2 - 1].x, normal[vn2 - 1].y, normal[vn2 - 1].z);
			tmpPNT.texture = D3DXVECTOR2(UV[uv2 - 1].x, UV[uv2 - 1].y);
			tmpSubMesh.vPNT_VERTEX.push_back(tmpPNT);

			tmpPNT.p = D3DXVECTOR3(vertex[v3 - 1].x, vertex[v3 - 1].y, vertex[v3 - 1].z);
			tmpPNT.normal = D3DXVECTOR3(normal[vn3 - 1].x, normal[vn3 - 1].y, normal[vn3 - 1].z);
			tmpPNT.texture = D3DXVECTOR2(UV[uv3 - 1].x, UV[uv3 - 1].y);
			tmpSubMesh.vPNT_VERTEX.push_back(tmpPNT);

				tmpSubMesh.vec_nFaceIndex.push_back(v1 - 1);
				tmpSubMesh.vec_nFaceIndex.push_back(v2 - 1);
				tmpSubMesh.vec_nFaceIndex.push_back(v3 - 1);
														
				tmpSubMesh.vec_nUV_Index.push_back(uv1 - 1);
				tmpSubMesh.vec_nUV_Index.push_back(uv2 - 1);
				tmpSubMesh.vec_nUV_Index.push_back(uv3 - 1);
			
		}
		else if (tmp == "g")
		{
			char s_GroupName[64];

			if ((sscanf_s(newline.c_str(), "%*s %s", s_GroupName, sizeof(s_GroupName))) != -1)
			{
				tmpSubMesh.sGroupName = s_GroupName;
			}
			else
			{
				if (isGroupStart)
				{
					tmpSubMesh.nCntTriangles = tmpSubMesh.vPNT_VERTEX.size()/3;
					tmpSubMesh.vecVertex = vertex;
					tmpSubMesh.vecUV = UV;
					CntFaces = tmpSubMesh.vecVertex.size();
					CntUVFaces = tmpSubMesh.vecUV.size();

					ret.push_back(tmpSubMesh);
					ZeroMemory(&tmpSubMesh, sizeof(tmpSubMesh));
					ZeroMemory(&tmpPNT, sizeof(tmpPNT));
					CntVertex += vertex.size();
					ZeroMemory(&vertex, sizeof(vertex));
					CntNormal += normal.size();
					ZeroMemory(&normal, sizeof(normal));
					CntUV += UV.size();
					ZeroMemory(&UV, sizeof(UV));					
				}
				else
					isGroupStart = !isGroupStart;
			}
		}
		else if (tmp == "usemtl")
		{
			static int mtlCnt = 0;
			char usemtl[64];

			sscanf_s(newline.c_str(), "%*s %s", &usemtl, sizeof(usemtl));
			tmpSubMesh.sMaterialName = usemtl;
			
			tmpSubMesh.mat9Material= GetMaterial( (path + fNameNoExt + ".mtl"), usemtl, &tmpSubMesh);
		}

	}

	in.close();

	return ret;
}

D3DMATERIAL9 ObjLoader::GetMaterial(string filename, string MatName, SubMesh *Dest)
{
	ifstream		in;
	string			newline;
	char			indicator[64];
	D3DMATERIAL9	ret;
	string			path;

	ZeroMemory(&ret, sizeof(ret));
	
	path = filename;
	
	size_t found = path.find_last_of("/");
	if(found != path.npos)
		path.erase(found + 1);
	

	in.open(filename, ios::in);
	while (!in.eof())
	{
		getline(in, newline);
		string tmp;
		sscanf_s(newline.c_str(), "%*s %s", indicator, sizeof(indicator));
		tmp = indicator;

		if (tmp == MatName)
		{
			while (newline[0] != '#')
			{
				getline(in, newline);				
				sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
				tmp = indicator;

				if (strstr(indicator, "Ka"))
				{
					sscanf_s(newline.c_str(), "%*s %f %f %f", &ret.Ambient.r, &ret.Ambient.g, &ret.Ambient.b);
					ret.Ambient.a = 1.0f;
				}
				else if (strstr(indicator, "map_Kd"))
				{
					string mapname;
					char map[64];
					sscanf_s(newline.c_str(), "%*s %s", map, sizeof(map));
					mapname = map;
					D3DXCreateTextureFromFileA(g_pD3DDevice, (path + mapname).c_str(), &Dest->tx9Texture);
					Dest->sTextureName = mapname;
				}
				else if (strstr(indicator, "Kd"))
				{
					sscanf_s(newline.c_str(), "%*s %f %f %f", &ret.Diffuse.r, &ret.Diffuse.g, &ret.Diffuse.b);
					ret.Diffuse.a = 1.0f;
				}
				else if (strstr(indicator, "Ks"))
				{
					sscanf_s(newline.c_str(), "%*s %f %f %f", &ret.Specular.r, &ret.Specular.g, &ret.Specular.b);
					ret.Specular.a = 1.0f;
				}
				else if (strstr(indicator, "d"))
				{
					sscanf_s(newline.c_str(), "%*s %f", &ret.Power);
				}
				
			}
		}
	}

	ret.Emissive = { 0.0f, 0.0f, 0.0f, 1.0f };
	return ret;

}
