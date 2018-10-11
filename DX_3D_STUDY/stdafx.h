// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define PI 3.141592f
#define EPSILON 0.00001f

#define	SAFE_RELEASE(p) { if(p) p->Release(); p = NULL;}
#define SAFE_DELETE(p)  { if(p) delete p; p = NULL;} 


// �̱��� ��ũ�� ����
#define SINGLETONE(class_name) \
public : \
	class_name(void);\
	~class_name(void);\
public: \
	static class_name* GetInstance() \
	{\
		static class_name instance; \
		return &instance;\
	}


//�ؽ��� ��ġ Ȯ�ο�.
// ����ũ����Ʈ 64 * 32 �ؽ��Ŀ�
#define	UV_x1 1 / 8.0000f
#define	UV_x2 2 / 8.0000f
#define	UV_x3 3 / 8.0000f
#define	UV_x4 4 / 8.0000f
#define	UV_x5 5 / 8.0000f
#define	UV_x6 6 / 8.0000f
#define	UV_x7 7 / 8.0000f

#define	UV_y1 1 / 4.0000f
#define	UV_y2 2 / 4.0000f
#define	UV_y3 3 / 4.0000f


// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// c++ ��Ÿ�� ��� ����
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <map>

#include <assert.h>


// ���̷�ƮX 9 �� ���̺귯�� �߰�
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")




using namespace std;


// �ܼ� ����� �޽��� â
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

// ������ �ڵ� ��������ȭ
extern HWND g_hWnd;


// D3DXVECTOR3		p;
// D3DCOLOR		color;
struct ST_PC_VERTEX
{
	D3DXVECTOR3		p;
	D3DCOLOR		color;

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

// D3DXVECTOR3			p;
// D3DXVECTOR3			normal;
// D3DXVECTOR2			texture;
struct ST_PNT_VERTEX
{
	D3DXVECTOR3			p;
	D3DXVECTOR3			normal;
	D3DXVECTOR2			texture;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};


// D3DXVECTOR3			p;
// D3DXVECTOR2			texture1;	 // UV Coord
struct ST_PT_VERTEX
{
	D3DXVECTOR3			p;
	D3DXVECTOR2			texture1;	 // UV Coord
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};


struct SubMesh {	
	string						sGroupName;
	string						sMaterialName;
	D3DMATERIAL9				mat9Material;
	string						sTextureName;
	LPDIRECT3DTEXTURE9			tx9Texture;
	vector<ST_PNT_VERTEX>		vPNT_VERTEX;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };	
};





// ����� ��Ÿ��
//#define SYNTHESIZE (varType, varName, FunName) \
//protected : varType varName; \
//public : inline varType Get##FunName(void) const {return varName;} \
//public : inline void Set##FunName(varType var) { varName = var; }
//
//#define SYNTHESIZE_PASS_BY_REF(varType, varName, FunName) \
//protected : varType varName; \
//public : inline varType& Get##FunName(void) {return varName;} \
//public : inline void Set##FunName(varType var) { varName = var; }


//#include "cCubeman.h"


// ����� ���� ��� ����
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cBoxman.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cHexagon.h"
#include "ObjLoader.h"
#include "cMap.h"
#include "Asciitok.h"