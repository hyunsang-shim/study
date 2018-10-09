#include "stdafx.h"
#include "ObjLoader.h"

#define MAX_SIZE 1000

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

void ObjLoader::ParseObj(string Filename)
{
	// v 정점 리스트 D3DXVECTOR3
	// 텍스쳐 u v w 좌표
	// 버텍스 노멀 값
	// 매터리얼 정보 파일 경로

	// 위의 정보를 토대로 	
	// g <그룹명> 으로 정의된 그룹이름의 sub mesh를 정의한다.
	// g <그룹명>에는 어떤 매터리얼을 사용 할 지 지정할 수 있다. (usemtl)

	vector<D3DXVECTOR3>		v_Vertices;
	vector<D3DXVECTOR3>		v_UVW;
	vector<D3DXVECTOR3>		v_Normal;
	vector<ST_PNT_VERTEX>	pnt_shape;

	string					s_groupName;
	string					s_materialName;

	
	ifstream fFile;
	fFile.open(Filename, ios_base::in);


	if (fFile.fail())
	{
		MessageBox(NULL, _T("파일을 찾을 수 없습니다."), _T("파일 열기 실패!"), MB_OK);
		return;
	}
	
	
	string			newline;
	int				v1, t1, n1;
	int				v2, t2, n2;
	int				v3, t3, n3;
	char			indicator[64];

	while (!fFile.eof())
	{
		getline(fFile, newline);

		sscanf_s(newline.c_str(), "%s", indicator, sizeof(indicator));

		if (strstr(indicator, "v "))
		{
			float x, y, z; 
			sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &y, &z);
			v_Vertices.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (strstr(indicator, "vt "))
		{
			float u, v, w;
			sscanf_s(newline.c_str(), "%*s %f %f %f", &u, &v, &w));
			v_UVW.push_back(D3DXVECTOR3(u, v, w));
		}
		else if (strstr(indicator, "vn "))
		{
			float x, y, z;
			sscanf_s(newline.c_str(), "%*s %f %f %f", &x, &y, &z);
			v_Normal.push_back(D3DXVECTOR3(x, y, z));
		}



	}



}

void ObjLoader::GetMaterialLib(string Filename)
{
}

void ObjLoader::GetTextures(string Filename)
{
}
