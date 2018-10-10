#include "stdafx.h"
#include "cNode.h"


cNode::cNode()
	: m_nKey(NULL)
	, m_nData(NULL)
	, m_pLChild(NULL)
	, m_pRChild(NULL)
{
}


cNode::~cNode()
{
}

cNode::cNode(int key, int data)
{
	m_nKey = key;
	m_nData = data;
	m_pLChild = NULL;
	m_pRChild = NULL;
}

void cNode::Insert(int key, int data)
{	
	if (this == NULL)
	{
		m_nKey = key;
		m_nData = data;
		m_pLChild = NULL;
		m_pRChild = NULL;
	}

	if (Find(key) != NULL)
	{
		printf("�ߺ��� Ű ���Դϴ�.\n�Էµ� ���� ���õ˴ϴ�. (�Է� : Key - %d, data - %d)\n", key, data);
		return;
	}
	else if (m_nKey > key)
		if (m_pLChild != NULL)
			m_pLChild->Insert(key, data);
		else
			m_pLChild = new cNode(key, data);
	else
	{
		if (m_pRChild != NULL)
			m_pRChild->Insert(key, data);
		else
			m_pRChild = new cNode(key, data);
	}
}

cNode * cNode::Find(int key)
{
	// ��Ʈ�� ������ (ù ������ �Է� ���� Find ���� �ϸ�)
	// null pointer�� ����	
	if (m_nKey == NULL)
		return NULL;

	// ã�� Ű ���� ���� ����� Ű ���� ���ٸ� ���� ��带 ����
	if (m_nKey == key)
		return this;
	// ã�� Ű ���� ���� ����� Ű �� ���� �۰�, ���� ��尡 NULL�� �ƴϸ� ���� ���� ����
	else if (m_nKey > key)
	{
		// ���� �ٴٸ��� NULL�� ����
		if (m_pLChild == NULL)
			return NULL;
		else
			m_pLChild->Find(key);
	}
	else if (m_nKey < key)
	{
		// ���� �ٴٸ��� NULL�� ����
		if (m_pRChild == NULL)
			return NULL;
		else
			// �ƴϸ� �ѹ� �� Ž��
			m_pRChild->Find(key);
	}
	else
		return NULL;
}

cNode * cNode::FindParent(int key)
{	
	// ã�� Ű ���� �ڽ����� ������ ������ ����
	if (m_pLChild != NULL)
	{
		if (m_pLChild->m_nKey == key)
			return this;
	}
	else if (m_pRChild != NULL)
	{
		if (m_pRChild->m_nKey == key)
			return this;
	}
	else
		return NULL;

	// ã�� Ű ���� ���� ����� Ű �� ���� �۰�, ���� ��尡 NULL�� �ƴϸ� ���� ���� ����
	if (m_nKey > key)
	{
		// ���� �ٴٸ��� NULL�� ����
		if (m_pLChild == NULL)
			return NULL;
		else
			m_pLChild->FindParent(key);
	}
	else if (m_nKey < key)
	{
		// ���� �ٴٸ��� NULL�� ����
		if (m_pRChild == NULL)
			return NULL;
		else
			// �ƴϸ� �ѹ� �� Ž��
			m_pRChild->FindParent(key);
	}
	else
		return NULL;
}

void cNode::Print()
{
	if (m_pLChild != NULL)
		m_pLChild->Print();
	
	printf("Key : %d, Data : %d\n", m_nKey, m_nData);

	if (m_pRChild != NULL)
		m_pRChild->Print();
}

void cNode::Delete(int key, cNode ** ppThis)
{
	cNode *target = (*ppThis)->Find(key);


	
	// ������ �׳� �����.
	if (target->GetLChild() == NULL)
	{
		if (target->GetRChild() == NULL)
		{
			// �����̹Ƿ�, �θ𿡰Լ� �ڽ��� NULL�� �����.
			if ((*ppThis)->GetKey() == key)
				(*ppThis)->SetLChild(NULL);
			else
			free(target);
		}
		else
			target->GetRChild()->GetMinNode();
	}
	else
	{
		target->Swap( ( (*ppThis)->Find(key) )->GetLChild()->GetMinNode());
	}

	if (target->GetMinNode() == NULL)
		free(target);
	else
	{
		while ((target->GetMinNode() != NULL))
			target->GetMinNode();
		
	}
	
}

cNode * cNode::GetMinNode()
{
	// ���� ���� ���� �� ��, �� �ڽ� ������ ���� �ٴϸ鼭
	// ���� ��� ���� ������, ���� ��� ������ ��� �� �߿� ���� ū ��带 ã�´�.
	
	// ȣ����(������ ���)�� Key ���� ��� ������ �Ѵ�.
	// ȣ������ ���� ��� ���� �ּ� ���� �ְ�
	// �� �ڷ� ������ ���� ���� ��� �� ���� �۰�, �ִ밪�̶�� �����Ѵ�.
	if (this->m_pRChild != NULL)
		this->m_pRChild->GetMinNode();
	else
		return this;
}

void cNode::Swap(cNode * target)
{
	cNode Swapper(m_nKey, m_nData);
	// �ӽ� ����ҿ� �ٲ� �� ����
	Swapper.m_pLChild = m_pLChild;
	Swapper.m_pRChild = m_pRChild;

	//////
	m_nKey = target->GetKey();
	m_nData = target->GetData();
	m_pLChild = target->GetLChild();
	m_pRChild = target->GetRChild();


	target->m_nKey =  GetKey();
	target->m_nData = GetData();
	target->m_pLChild = GetLChild();
	target->m_pRChild = GetRChild();


}
