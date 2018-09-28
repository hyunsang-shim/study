#pragma once
class cNode;

class cBST
{
public:
	cBST();
	~cBST();

private:
	cNode* m_pRoot;

public:
	void Insert(int key, int data);
	cNode* Find(int key);
	cNode* FindParent(int key);
	void Delete(int key);
	void Print();
};

