// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define PI 3.141592f
#define EPSILON 0.00001f

#define	SAFE_RELEASE(p) { if(p) p->Release(); p = NULL;}
#define SAFE_DELETE(p)  { if(p) delete p; p = NULL;} 
#define SAFE_DELETE_ARRAY(p) {if(p) delete[] p; p = NULL;}

// 싱글톤 매크로 설정
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


//텍스쳐 위치 확인용.
// 마인크래프트 64 * 32 텍스쳐용
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


// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// c++ 런타임 헤더 파일
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <map>

#include <assert.h>


// 다이렉트X 9 용 라이브러리 추가
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")




using namespace std;


// 콘솔 디버그 메시지 창
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

// 윈도우 핸들 전역변수화
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
	string						sTextureName;
	D3DMATERIAL9				mat9Material;
	LPDIRECT3DTEXTURE9			tx9Texture;
	vector<D3DXVECTOR3>			vecVertex;
	vector<D3DXVECTOR2>			vecUV;
	vector<WORD>				vec_nFaceIndex;
	vector<WORD>				vec_nUV_Index;
	vector<ST_PNT_VERTEX>		vPNT_VERTEX;
	int							nCntTriangles;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };	
};

// string						meshName;
// string						MaterialName;
// string						TextureName;
// D3DMATERIAL9					mat9Material;
// string						sTextureName;
// LPDIRECT3DTEXTURE9			tx9Texture;
// vector<ST_PNT_VERTEX>		vPNT_VERTEX;
struct ASE_Obj {
	string						meshName;
	string						MaterialName;
	int							parentNodeIdx;
	string						ParentNodeName;
	D3DXMATRIXA16				ParentWorld;
	D3DXMATRIXA16				ParentWorldInverse;
	D3DXMATRIXA16				matMyLocal;
	D3DXMATRIXA16				matMyWorld;
	string						MyNodeName;
	D3DXVECTOR3					LocalScale;
	D3DXVECTOR3					LocalRotation; 
	D3DXVECTOR3					LocalPosition;
	unsigned short				Timevalue;
	string						TextureName;
	D3DMATERIAL9				mat9Material;
	LPDIRECT3DTEXTURE9			tx9Texture;
	vector<ST_PNT_VERTEX>		vPNT_VERTEX;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_RHWC_VERTEX
{
	D3DXVECTOR4	p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_POS_SAMPLE
{
	int				n;
	D3DXVECTOR3		v;
	ST_POS_SAMPLE()
		:n(0)
		, v(0, 0, 0)
	{
	}
};

struct ST_ROT_SAMPLE
{
	int				n;
	D3DXQUATERNION	q;
	ST_ROT_SAMPLE()
		: n(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};




// 강사님 스타일
#define SYNTHESIZE(varType,varName,funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const {return varName;}\
public: inline void Set##funName(varType var){varName = var;}

#define SYNTHESIZE_PASS_BY_REF(varType,varName,funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) {return varName;}\
public: inline void Set##funName(varType& var){varName = var;}

#define SAFE_ADD_REF(p) {if(p) p->AddRef();}

#define SYNTHESIZE_ADD_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const {return varName;}\
public: virtual void Set##funName(varType var){\
if(varName != var){\
SAFE_ADD_REF(var);\
SAFE_RELEASE(varName);\
varName=var;\
}\
}
// 사용자 정의 헤더 파일
#include "cCubePC.h"
#include "cBoxman.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cHexagon.h"
#include "ObjLoader.h"
#include "cMap.h"
#include "Asciitok.h"
//#include "cASELoader.h"
#include "cASE_Char.h"
// 강사님 ASE 로더
#include "cObject.h"
#include "cObjectManager.h"
#include "cTextureManager_inst.h"
#include "cFrame.h"
#include "cAseLoader_inst.h"
#include "cDeviceManager.h"
#include "cRawLoader.h"
#include "cHeightMap.h"
#include "cLoadXFile.h"
#include "cTimerManager.h"
#include "cFrustumCulling.h"

//#include "cCubeman.h"
