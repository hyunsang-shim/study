#pragma once

class cNode;
typedef cNode* LPNODE;

class cNode
{

private:
	SYNTHESIZE(int, m_nKey, Key);
	SYNTHESIZE(int, m_nData, Data);
	SYNTHESIZE(cNode*, m_pLChild, LChild);
	SYNTHESIZE(cNode*, m_pRChild, RChild);

public:
	cNode();
	~cNode();


	cNode(int key, int data);

	void Insert(int key, int data);
	cNode* Find(int key);
	cNode* FindParent(int key);
	void Print();
	void Delete(int key, cNode** ppThis);
	cNode* GetMinNode();
	void Swap(cNode* target);
};

