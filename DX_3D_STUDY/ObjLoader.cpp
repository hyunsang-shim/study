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
	// v ���� ����Ʈ D3DXVECTOR3
	// �ؽ��� u v w ��ǥ
	// ���ؽ� ��� ��
	// ���͸��� ���� ���� ���

	// ���� ������ ���� 	
	// g <�׷��> ���� ���ǵ� �׷��̸��� sub mesh�� �����Ѵ�.
	// g <�׷��>���� � ���͸����� ��� �� �� ������ �� �ִ�. (usemtl)

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
		MessageBox(NULL, _T("������ ã�� �� �����ϴ�."), _T("���� ���� ����!"), MB_OK);
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
