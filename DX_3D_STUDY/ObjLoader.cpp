#include "stdafx.h"
#include "ObjLoader.h"

#define MAX_SIZE 1000

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

vector<ST_PNT_SubMesh> ObjLoader::ParseObj(string Filename)
{
	// v 정점 리스트 D3DXVECTOR3
	// 텍스쳐 u v w 좌표
	// 버텍스 노멀 값
	// 매터리얼 정보 파일 경로

	// 위의 정보를 토대로 	
	// g <그룹명> 으로 정의된 그룹이름의 sub mesh를 정의한다.
	// g <그룹명>에는 어떤 매터리얼을 사용 할 지 지정할 수 있다. (usemtl)

	// 중간 입력 및 저장용 변수
	vector<D3DXVECTOR3>		v_Vertices;
	vector<D3DXVECTOR3>		v_UVW;
	vector<D3DXVECTOR3>		v_Normal;
	ST_PNT_SubMesh			tmpPNT;
	string					s_groupName;
	string					s_materialName;

	// 리턴값을 위한 변수
	vector<ST_PNT_SubMesh>	ret;

	
	ifstream fFile;
	fFile.open(Filename, ios_base::in);


	if (fFile.fail())
	{
		MessageBox(NULL, _T("파일을 찾을 수 없습니다."), _T("파일 열기 실패!"), MB_OK);
		return vector<ST_PNT_SubMesh>(NULL);
	}	
	
	string			newline;
	char			indicator[64];

	while (!fFile.eof())
	{
		getline(fFile, newline);
		string tmp;
		sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
		tmp = indicator;


		if (tmp == "v")
		{
			float x, y, z;
			sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &y, &z);
			v_Vertices.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (tmp == "vt")
		{
			float u, v, w;
			sscanf_s(newline.c_str(), "%*s %f %f %f", &u, &v, &w);
			v_UVW.push_back(D3DXVECTOR3(u, v, w));
		}
		else if (tmp == "vn")
		{
			float x, y, z;
			sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &y, &z);
			v_Normal.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (tmp == "f")
		{
			int vx = 0, vy = 0, vz = 0;
			int u = 0, v = 0, w = 0;
			int vnx = 0, vny = 0, vnz = 0;

			sscanf(newline.c_str(), 
				"%*s %d/%d/%d %d/%d/%d %d/%d/%d", &vx, &u, &vnx, &vy, &v, &vny, &vz, &w, &vnz);
			
			tmpPNT.p.x = v_Vertices[vx - 1].x;
			tmpPNT.p.y = v_Vertices[vy - 1].y;
			tmpPNT.p.z = v_Vertices[vz - 1].z;

			tmpPNT.texture.x = v_UVW[u - 1].x;
			tmpPNT.texture.y = v_UVW[v - 1].y;

			tmpPNT.normal.x = v_Normal[vnx - 1].x;
			tmpPNT.normal.y = v_Normal[vny - 1].y;
			tmpPNT.normal.z = v_Normal[vnz - 1].z;
			
			ret.push_back(tmpPNT);
		}
		else if (tmp == "g")
		{
			char s_GroupName[64];
						
			if ( (sscanf_s(newline.c_str(), "%*s %s", s_GroupName, sizeof(s_GroupName))) != -1)
			{	
				tmpPNT.GroupName = s_GroupName;
			}
		}	
		else if (tmp == "usemtl")
		{
			char usemtl[64];

			sscanf_s(newline.c_str(), "%*s %s", &usemtl, sizeof(usemtl));
			tmpPNT.MaterialName = usemtl;
		}
		
	}

	fFile.close();

	return ret;
}

map<string, MATERIAL> ObjLoader::GetMaterialLib(string Filename)
{
	// 중간 입력 및 저장용 변수
	string						LibraryPath;
	MATERIAL					tmpMtl;
		

	// 리턴용 변수
	map<string, MATERIAL>		ret;
	

	ifstream fFile_obj;	
	fFile_obj.open(Filename, ios_base::in);


	if (fFile_obj.fail())
	{
		MessageBox(NULL, _T("파일을 찾을 수 없습니다."), _T("파일 열기 실패!"), MB_OK);
		return map<string, MATERIAL>(NULL,NULL);
	}

	string			newline;
	char			indicator[64];

	while (!fFile_obj.eof())
	{
		getline(fFile_obj, newline);
		string tmp;
		sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
		tmp = indicator;

		if (tmp == "mtllib")
		{
			char mtllib[64];
			sscanf_s(newline.c_str(), "%*s %s", &mtllib, sizeof(mtllib));
			LibraryPath = mtllib;
			break;
		}
	}

	fFile_obj.close();


	string			tmpName;
	MATERIAL		tmpMtl;
	string			strPath = "obj/";

	ifstream fFile_mtl;
	fFile_mtl.open(LibraryPath, ios_base::in);


	if (fFile_mtl.fail())
	{
		MessageBox(NULL, _T("파일을 찾을 수 없습니다."), _T("파일 열기 실패!"), MB_OK);
		return map<string, MATERIAL>(NULL, NULL);
	}


	int cnt = 0;
	while (!fFile_mtl.eof())
	{
		getline(fFile_mtl, newline);
		string tmp;
		sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));
		tmp = indicator;

		if (tmp == "newmtl")
		{
			if (cnt != 0)
			{
				tmpMtl.material.Emissive(1.0f, 1.0f, 1.0f);
				ret.insert(make_pair(tmpName, tmpMtl));
			}
			char mtlName[64];
			sscanf_s(newline.c_str(), "%*s %s", &mtlName, sizeof(mtlName));
			tmpName = mtlName;
			cnt++;
		}
		else if (tmp == "Ka")
		{
			float aR, aG, aB, aA;

			if (sscanf_s(newline.c_str(), "%*s %f %f %f %f", &aR, &aG, &aB, &aA) < 4)
				aA = 1.0f;

			tmpMtl.material.Ambient.r = aR;
			tmpMtl.material.Ambient.g = aR;
			tmpMtl.material.Ambient.b = aR;
			tmpMtl.material.Ambient.a = aA;
		}
		else if (tmp == "Kd")
		{
			float dR, dG, dB, dA;

			if (sscanf_s(newline.c_str(), "%*s %f %f %f %f", &dR, &dG, &dB, &dA) < 4)
				dA = 1.0f;

			tmpMtl.Diffuse.r = dR;
			tmpMtl.Diffuse.g = dR;
			tmpMtl.Diffuse.b = dR;
			tmpMtl.Diffuse.a = dA;

		}
		else if (tmp == "Ks")
		{
			float sR, sG, sB, sA;

			if (sscanf_s(newline.c_str(), "%*s %f %f %f %f", &sR, &sG, &sB, &sA) < 4)
				sA = 1.0f;

			tmpMtl.material.Specular.r = sR;
			tmpMtl.material.Specular.g = sR;
			tmpMtl.material.Specular.b = sR;
			tmpMtl.material.Specular.a = sA;

		}
		else if (tmp == "map_Kd")
		{	
			char tmpTextureName[128];

			sscanf_s(newline.c_str(), "%*s %s", &tmpTextureName, sizeof(tmpTextureName));
			tmpMtl.textureName = tmpTextureName;
		}
	}	


	if (ret.size() < cnt)
		ret.insert(make_pair(tmpName, tmpMtl));


	fFile_mtl.close();

	return ret;
}

map<string, string> ObjLoader::GetTextures(map<string, MATERIAL > MaterialLibraryName)
{
	map<string, string>			map_ret;
	string						strPath = ".obj/";

	for (int i = 0; i < MaterialLibraryName.size(); i++)
	{
		map_ret.insert(make_pair(MaterialLibraryName[i].textureName, strPath + MaterialLibraryName[i].textureName));
	}

	return map_ret;
}
