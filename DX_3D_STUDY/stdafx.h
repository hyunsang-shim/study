// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

// �ܼ� ����� �޽��� â
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <time.h>

using namespace std;
#include <assert.h>>


#define PI 3.141592f
#define EPSILON 0.00001f

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

// ���̷�ƮX 9 �� ���̺귯�� �߰�
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// ������ �ڵ� ��������ȭ
extern HWND g_hWnd;

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
#define	x1 1 / 8.0000f
#define	x2 2 / 8.0000f
#define	x3 3 / 8.0000f
#define	x4 4 / 8.0000f
#define	x5 5 / 8.0000f
#define	x6 6 / 8.0000f
#define	x7 7 / 8.0000f

#define	y1 1 / 4.0000f
#define	y2 2 / 4.0000f
#define	y3 3 / 4.0000f


struct ST_PC_VERTEX
{
	D3DXVECTOR3		p;
	D3DCOLOR		color;

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};


struct ST_PNT_VERTEX
{
	D3DXVECTOR3			p;
	D3DXVECTOR3			normal;
	D3DXVECTOR2			texture;
	enum{ FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3			p;
	D3DXVECTOR2			texture1;	 // UV Coord
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};


//#define SYNTHESIZE (varType, varName, FunName) \
//protected : varType varName; \
//public : inline varType Get##FunName(void) const {return varName;} \
//public : inline void Set##FunName(varType var) { varName = var; }
//
//#define SYNTHESIZE_PASS_BY_REF(varType, varName, FunName) \
//protected : varType varName; \
//public : inline varType& Get##FunName(void) {return varName;} \
//public : inline void Set##FunName(varType var) { varName = var; }


#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cBoxman.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cHexagon.h"
//#include "cCubeman.h"


