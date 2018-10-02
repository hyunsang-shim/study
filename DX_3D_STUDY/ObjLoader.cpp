#include "stdafx.h"
#include "ObjLoader.h"

#define MAX_SIZE 1000

ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

vector<ST_PNT_VERTEX> ObjLoader::ParseObj(char* Filename)
{

	vector<ST_PNT_VERTEX> ret;
	vector<D3DXVECTOR3> vertex;
	vector<D3DXVECTOR2> texture;
	vector<D3DXVECTOR3> normal;

	FILE *fsObjFile;
	char inputTemp[MAX_SIZE];	
	
	fsObjFile = fopen(Filename, "r");
	
	if (fsObjFile != NULL)	
	{
		int a = 0;
		float x, y, z;
		int v1, t1, n1;
		int v2, t2, n2;
		int v3, t3, n3;

		while (fgets(inputTemp, MAX_SIZE, fsObjFile))
		{
			if (strstr(inputTemp, "v "))
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
				ST_PNT_VERTEX tmp;
				
				tmp.p = vertex[v1 - 1];
				tmp.texture = texture[t1 - 1];
				tmp.normal = normal[n1 - 1];
				ret.push_back(tmp);
				
				printf("\n");
				tmp.p = vertex[v2 - 1];
				tmp.texture = texture[t2 - 1]; 
				tmp.normal = normal[n2 - 1];				
				ret.push_back(tmp);

				tmp.p = vertex[v3 - 1];
				tmp.texture = texture[t3 - 1]; 
				tmp.normal = normal[n3 - 1];
				
				ret.push_back(tmp);

				//printf("point%d = x %f y %f Z %f\n", a, ret[a*3].p.x, ret[a*3+1].p.y, ret[a*3+2].p.z);				
			}
			a++;
		}
	}
	else
	{
		MessageBox(NULL, _T("파일을 찾을 수 없습니다.\n프로그램을 종료합니다."), _T("Fail!"), MB_OK);
		SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		return ret;
	}

	fcloseall();


	return ret;

	/*
	char szTemp[1024];
	fgets(....);
	float x, y, z;

	sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);

	
	*/
}

MATERIAL ObjLoader::GetMaterial(char * Filename) {
	MATERIAL tmp;
	FILE *fsObjFile;
	char inputTemp[MAX_SIZE];

	fsObjFile = fopen(Filename, "r");

	if (fsObjFile != NULL)
	{
		int a = 0;

		while (fgets(inputTemp, MAX_SIZE, fsObjFile))
		{
			if (strstr(inputTemp, "Ka "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &tmp.Ambient.r, &tmp.Ambient.g, &tmp.Ambient.b);
			}
			else if (strstr(inputTemp, "Kd "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &tmp.Diffuse.r, &tmp.Diffuse.g, &tmp.Diffuse.b);
			}
			else if (strstr(inputTemp, "Ks "))
			{
				sscanf_s(inputTemp, "%*s %f %f %f", &tmp.Specular.r, &tmp.Specular.g, &tmp.Specular.b);
			}
			else if (strstr(inputTemp, "d "))
			{
				sscanf_s(inputTemp, "%*s %f", &tmp.Power);
			}
			else if (strstr(inputTemp, "Ns "))
			{
				sscanf_s(inputTemp, "%*s %f", &tmp.Ns);
			}
			else if (strstr(inputTemp, "illum "))
			{
				sscanf_s(inputTemp, "%*s %f", &tmp.Illumination);
			}
		}

		fcloseall();
		return tmp;
	}
}