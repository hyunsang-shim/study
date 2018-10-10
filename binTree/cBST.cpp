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

void cBST::Delete(int key)
{
	// Key ���� �θ� ��带 ã�´�.

	// �θ� ��� ����� ���� temp
	m_pRoot->Delete(key, &m_pRoot);
}

void cBST::Print()
{
	m_pRoot->Print();
}
