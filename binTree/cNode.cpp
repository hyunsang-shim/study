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
		printf("중복된 키 값입니다.\n입력된 값은 무시됩니다. (입력 : Key - %d, data - %d)\n", key, data);
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
	// 루트가 없으면 (첫 데이터 입력 전에 Find 먼저 하면)
	// null pointer를 리턴	
	if (m_nKey == NULL)
		return NULL;

	// 찾는 키 값이 현재 노드의 키 값과 같다면 현재 노드를 리턴
	if (m_nKey == key)
		return this;
	// 찾는 키 값이 현재 노드의 키 값 보다 작고, 왼쪽 노드가 NULL이 아니면 왼쪽 노드로 진입
	else if (m_nKey > key)
	{
		// 끝에 다다르면 NULL을 리턴
		if (m_pLChild == NULL)
			return NULL;
		else
			m_pLChild->Find(key);
	}
	else if (m_nKey < key)
	{
		// 끝에 다다르면 NULL을 리턴
		if (m_pRChild == NULL)
			return NULL;
		else
			// 아니면 한번 더 탐색
			m_pRChild->Find(key);
	}
	else
		return NULL;
}

cNode * cNode::FindParent(int key)
{	
	// 찾는 키 값을 자식으로 가지고 있으면 리턴
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

	// 찾는 키 값이 현재 노드의 키 값 보다 작고, 왼쪽 노드가 NULL이 아니면 왼쪽 노드로 진입
	if (m_nKey > key)
	{
		// 끝에 다다르면 NULL을 리턴
		if (m_pLChild == NULL)
			return NULL;
		else
			m_pLChild->FindParent(key);
	}
	else if (m_nKey < key)
	{
		// 끝에 다다르면 NULL을 리턴
		if (m_pRChild == NULL)
			return NULL;
		else
			// 아니면 한번 더 탐색
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


	
	// 리프면 그냥 지운다.
	if (target->GetLChild() == NULL)
	{
		if (target->GetRChild() == NULL)
		{
			// 리프이므로, 부모에게서 자신을 NULL로 만든다.
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
	// 왼쪽 노드로 진입 한 후, 그 자식 노드들을 따라 다니면서
	// 시작 노드 보다 작지만, 시작 노드 왼쪽의 노드 들 중에 가장 큰 노드를 찾는다.
	
	// 호출자(삭제할 노드)의 Key 값을 대상 값으로 한다.
	// 호출자의 왼쪽 노드 값을 최소 값에 넣고
	// 그 뒤로 오른쪽 놈을 봐서 대상 값 보다 작고, 최대값이라면 리턴한다.
	if (this->m_pRChild != NULL)
		this->m_pRChild->GetMinNode();
	else
		return this;
}

void cNode::Swap(cNode * target)
{
	cNode Swapper(m_nKey, m_nData);
	// 임시 저장소에 바뀔 값 대피
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
