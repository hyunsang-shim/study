#include "stdafx.h"
#include "cBST.h"
#include "cNode.h"

cBST::cBST()
	: m_pRoot(NULL)
{
}


cBST::~cBST()
{
}

void cBST::Insert(int key, int data)
{
	if (m_pRoot == NULL)
		m_pRoot = new cNode(key, data);
	else
		m_pRoot->Insert(key, data);
}

cNode * cBST::Find(int key)
{		
	return m_pRoot->Find(key);
}

cNode * cBST::FindParent(int key)
{
	return m_pRoot->FindParent(key);
}

void cBST::Delete(int key)
{
	// Key ���� �θ� ��带 ã�´�.

	// �θ� ��� ����� ���� temp
	cNode* temp = this->FindParent(key);

	FindParent(key)->Delete(key, &temp);
}

void cBST::Print()
{
	m_pRoot->Print();
}
