#pragma once
// �̱��� ���� Ȱ��.
// �̱��� �⺻�� : ����� �ۼ�

class cCouncil {
public:
	cCouncil();
	~cCouncil();

	static cCouncil *GetInstance()
	{
		static cCouncil instance;
		return &instance;
	}

	//���� �ڵ忡 ���� �ۼ�

};

#define g_Council cCouncil::GetInstance()

