// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <malloc.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#define SYNTHESIZE(varType, varName, funName) \
private : varType varName;\
public :  varType Get##funName(void) const{ return varName;}\
public : void Set##funName(varType var) {varName = var;}

#define SAFEDELETE(p) if(p) { delete (p); (p) = NULL;}

