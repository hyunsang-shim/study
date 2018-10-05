#include "stdafx.h"
#include "ObjLoader.h"

#define MAX_SIZE 1000

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

vector<OBJ_IMPORTER> ObjLoader::ParseObj(char* Filename)
{
	vector<OBJ_IMPORTER>			obj_ret;
	OBJ_IMPORTER					tmp_obj;

	vector<string>					vec_objGroupName;
	char							objGroupName[128];
	vector<ST_PNT_VERTEX>			vec_vertexPNT;
	char							mtlLibName[128];
	char							mtl_name[128];
	map<string, MATERIAL>			map_material;
	vector<LPDIRECT3DTEXTURE9>		vec_textures;
	
	string							tmpString;
	ST_PNT_VERTEX					tmpPNT;
	vector<D3DXVECTOR3>				vertex;
	vector<D3DXVECTOR2>				texture;
	vector<D3DXVECTOR3>				normal;

	


	FILE *fsObjFile;
	char inputTemp[MAX_SIZE];	
	
	fsObjFile = fopen(Filename, "r");
	
	if (fsObjFile != NULL)	
	{
		int cnt = 0;
		float x, y, z;
		int v1, t1, n1;
		int v2, t2, n2;
		int v3, t3, n3;		

		while (fgets(inputTemp, MAX_SIZE, fsObjFile))
		{

			if (strstr(inputTemp, "mtllib"))
			{
				sscanf_s(inputTemp, "%*s %s", mtlLibName, sizeof(mtlLibName));
				map_material = GetMaterial(mtlLibName);
			}
			else if (strstr(inputTemp, "g "))
			{
				sscanf_s(inputTemp, "%*s %s", objGroupName, sizeof(objGroupName));
				tmp_obj.objGroupName.push_back(objGroupName);
			}
			else if (strstr(inputTemp, "v "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &x, &y, &z);
				vertex.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (strstr(inputTemp, "vt "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &x, &y, &z);
				texture.push_back(D3DXVECTOR2(x, y));
			}
			else if(strstr(inputTemp, "vn "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &x, &y, &z);
				normal.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (strstr(inputTemp, "f "))
			{
				sscanf_s(inputTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);				
				//printf("point%d = x %f y %f Z %f\n", a, ret[a*3].p.x, ret[a*3+1].p.y, ret[a*3+2].p.z);				

				ST_PNT_VERTEX tmp;

				tmp.p = vertex[v1 - 1];
				tmp.texture = texture[t1 - 1];
				tmp.normal = normal[n1 - 1];
				vec_vertexPNT.push_back(tmp);

				printf("\n");
				tmp.p = vertex[v2 - 1];
				tmp.texture = texture[t2 - 1];
				tmp.normal = normal[n2 - 1];
				vec_vertexPNT.push_back(tmp);

				tmp.p = vertex[v3 - 1];
				tmp.texture = texture[t3 - 1];
				tmp.normal = normal[n3 - 1];
				vec_vertexPNT.push_back(tmp);

			}
			else if (strstr(inputTemp, "usemtl "))
			{
				sscanf_s(inputTemp, "%*s %s", &mtl_name, sizeof(mtl_name));
				string strMtl_Name = mtl_name;
				tmp_obj.material.insert(make_pair(strMtl_Name, map_material.find(strMtl_Name)->second));
			}


			if (inputTemp[0] == 'g' && inputTemp[1] == '\n')
			{	
				
				if (!obj_ret.empty() && !tmp_obj.vertexPNT.empty())
				{
					tmp_obj.vertexPNT = vec_vertexPNT;
					tmp_obj.textures = vec_textures;
					tmp_obj.material = map_material;

					obj_ret.push_back(tmp_obj);
				}
				else
					obj_ret.resize(++cnt);

			}

			ZeroMemory(inputTemp, MAX_SIZE);
		}
	}
	else
	{
		MessageBox(NULL, _T("파일을 찾을 수 없습니다.\n프로그램을 종료합니다."), _T("Fail!"), MB_OK);
		SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		return obj_ret;
	}

	fclose(fsObjFile);
	
	return obj_ret;

}

map<string, MATERIAL> ObjLoader::GetMaterial(char * Filename) {
	
	map<string, MATERIAL>	materialMap;
	vector<string>			mtl_name;
	vector<MATERIAL>		mtl_mtl;
	D3DXCOLOR				tmpColor;
	float					tmpFloat;
	
	FILE					*fsMtlFile;
	char					inputTemp[MAX_SIZE];
	char					materialName[128];
	char					textureName[128];
	string					tmpname = Filename;

	int						cnt = 0;

	while (strstr(tmpname.c_str(), "/") != NULL)
	{
		size_t pos = tmpname.find("/");
		tmpname.replace(pos, 1, "\\");
	}

	fsMtlFile = fopen(tmpname.c_str(), "r");

	if (fsMtlFile != NULL)
	{

		while (fgets(inputTemp, MAX_SIZE, fsMtlFile))
		{
			mtl_mtl.resize(cnt);

			if (strstr(inputTemp, "newmtl "))
			{
				sscanf_s(inputTemp, "%*s %s", &materialName, sizeof(materialName));
				mtl_name.push_back(materialName);
				cnt = mtl_name.size();
			}
			else if (strstr(inputTemp, "map_Kd"))
			{
				sscanf_s(inputTemp, "%*s %s", &textureName, sizeof(textureName));
				mtl_mtl[cnt-1].Texture = GetTexture(textureName);
			}
			else if (strstr(inputTemp, "Ka "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &mtl_mtl[cnt - 1].Ambient.r, &mtl_mtl[cnt - 1].Ambient.g, &mtl_mtl[cnt - 1].Ambient.b);
				
			}
			else if (strstr(inputTemp, "Kd "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &mtl_mtl[cnt - 1].Diffuse.r, &mtl_mtl[cnt - 1].Diffuse.g, &mtl_mtl[cnt - 1].Diffuse.b);

			}
			else if (strstr(inputTemp, "Ks "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &mtl_mtl[cnt - 1].Specular.r, &mtl_mtl[cnt - 1].Specular.g, &mtl_mtl[cnt - 1].Specular.b);

			}
			else if (strstr(inputTemp, "d "))
			{
				sscanf_s(inputTemp, "%*s %f", &mtl_mtl[cnt - 1].Power);

			}
			else if (strstr(inputTemp, "Ns "))
			{
				sscanf_s(inputTemp, "%*s %f", &mtl_mtl[cnt - 1].Ns);

			}
			else if (strstr(inputTemp, "illum "))
			{
				sscanf_s(inputTemp, "%*s %f", &mtl_mtl[cnt - 1].Illumination);
			}

		}
		
		for (int i = 0; i < mtl_mtl.size(); i++)
			materialMap.insert(make_pair(mtl_name[i], mtl_mtl[i]));

		fclose(fsMtlFile);

		return materialMap;
	}
}

LPDIRECT3DTEXTURE9 ObjLoader::GetTexture(char * fileName)
{
	string					tmpname = fileName;
	LPDIRECT3DTEXTURE9		ret;

	while (strstr(tmpname.c_str(), "/") != NULL)
	{
		size_t pos = tmpname.find("/");
		tmpname.replace(pos, 1, "\\");
	}

	D3DXCreateTextureFromFileA(g_pD3DDevice, tmpname.c_str(), &ret);

	return ret;
}
