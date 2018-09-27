// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

// 콘솔 디버그 메시지 창
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
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

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

// 다이렉트X 9 용 라이브러리 추가
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// 윈도우 핸들 전역변수화
extern HWND g_hWnd;

#define	SAFE_RELEASE(p) { if(p) p->Release(); p = NULL;}
#define SAFE_DELETE(p)  { if(p) delete p; p = NULL;} 

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


