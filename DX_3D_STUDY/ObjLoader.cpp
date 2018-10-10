#include "stdafx.h"
#include "ObjLoader.h"

#define MAX_SIZE 1000

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

vector<SubMesh> ObjLoader::ParseObj()
{
	ifstream					in;
	string						newline;
	char						indicator[64];
	bool						isGroupStart = false;
	string						filename("box");


	vector<SubMesh>				ret;		// 리턴 할 구조체 vector
	SubMesh						tmpSubMesh; // 리턴용에 push할 임시 구조체
	ST_PNT_VERTEX				tmpPNT;
	vector<D3DXVECTOR3>			vertex;
	vector<D3DXVECTOR3>			normal;
	vector<D3DXVECTOR2>			UV;
	

	

	in.open("./obj/" + filename + ".obj", ios::in);

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
			int vx = 0, vy = 0, vz = 0;
			int u = 0, v = 0, w = 0;
			int vnx = 0, vny = 0, vnz = 0;

			sscanf(newline.c_str(),
				"%*s %d/%d/%d %d/%d/%d %d/%*d/%d", &vx, &u, &vnx, &vy, &v, &vny, &vz, &vnz);
			tmpPNT.p = D3DXVECTOR3(vertex[vx-1].x, vertex[vy-1].y, vertex[vz-1].z);
			tmpPNT.normal = D3DXVECTOR3(normal[vnx-1].x, normal[vny-1].y, normal[vnz-1].z);
			tmpPNT.texture = D3DXVECTOR2(UV[u-1].x, UV[v-1].y);
			tmpSubMesh.vPNT_VERTEX.push_back(tmpPNT);
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
					ret.push_back(tmpSubMesh);
					::ZeroMemory(&tmpPNT, sizeof(tmpPNT));
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
			tmpSubMesh.mat9Material= GetMaterial(filename, usemtl, &tmpSubMesh);
		}

	}

	in.close();
	for (int i = 0; i < ret.size(); i++)
	{
		printf("Groupname [ %s ] === Material [ %s ] === Texture Name [ %s ]\n", ret[i].sGroupName, ret[i].sMaterialName, ret[i].sTextureName);
		for (int k = 0; k < ret[i].vPNT_VERTEX.size(); k++)
		{
			printf("PNT#%03d : x %d  y %d  z %d\n", k, ret[i].vPNT_VERTEX[k].p.x, ret[i].vPNT_VERTEX[k].p.y, ret[i].vPNT_VERTEX[k].p.z);
		}
	}



	return ret;
}

D3DMATERIAL9 ObjLoader::GetMaterial(string filename, string MatName, SubMesh *Dest)
{
	ifstream		in;
	string			newline;
	char			indicator[64];
	D3DMATERIAL9	ret;
	ZeroMemory(&ret, sizeof(ret));

	in.open("./obj/" + filename + ".mtl", ios::in);
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
				sscanf_s(newline.c_str(), "%*s %s", indicator, sizeof(indicator));
				tmp = indicator;

				if (strstr(indicator, "Ka"))
				{
					sscanf_s(newline.c_str(), "%*s %f %f %f", &ret.Ambient.r, &ret.Ambient.g, &ret.Ambient.b);
					ret.Ambient.a = 1.0f;
				}
				else if (strstr(indicator, "Kd"))
				{
					sscanf_s(newline.c_str(), "%*s %f %f %f", ret.Diffuse.r, ret.Diffuse.g, ret.Diffuse.b);
					ret.Diffuse.a = 1.0f;
				}
				else if (strstr(indicator, "Ks"))
				{
					sscanf_s(newline.c_str(), "%*s %f %f %f", ret.Specular.r, ret.Specular.g, ret.Specular.b);
					ret.Specular.a = 1.0f;
				}
				else if (strstr(indicator, "d"))
				{
					sscanf_s(newline.c_str(), "%*s %f", ret.Power);
				}
				else if (strstr(indicator, "illum"))
				{
					sscanf_s(newline.c_str(), "%*s %f", ret.Emissive);
				}
				else if (strstr(indicator, "map_Kd"))
				{
					string mapname;
					sscanf_s(newline.c_str(), "%*s %s", mapname);
					D3DXCreateTextureFromFileA(g_pD3DDevice, mapname.c_str(), &Dest->tx9Texture);
					Dest->sTextureName = mapname;
				}
			}
		}
	}

	return ret;

}
