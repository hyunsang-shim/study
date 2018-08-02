#pragma once
class cManager
{
public:
	cManager();
	~cManager();
	int GetCurScene();



public:
	static cManager* GetInstance()
	{
		static cManager instance;

		return &instance;
	}

private:
	int CurScene;
};

