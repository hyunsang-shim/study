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

	printf("Filename : %s||\n", Filename);
	printf("Filename.c_str() : %s||\n", Filename.c_str());
	ifstream fFile;
	fFile.open(Filename, ios_base::in);

	if (fFile.fail())
	{
		MessageBox(NULL, _T("������ ã�� �� �����ϴ�."), _T("���� ���� ����!"), MB_OK);
		return;
	}
	
	
	string			newline;
	float			x, y, z;
	int				v1, t1, n1;
	int				v2, t2, n2;
	int				v3, t3, n3;

	while (!fFile.eof())
	{
		getline(fFile, newline);
	}



}

void ObjLoader::GetMaterialLib(string Filename)
{
}

void ObjLoader::GetTextures(string Filename)
{
}
