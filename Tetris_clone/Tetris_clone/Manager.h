#pragma once
class Manager
{
public:
	Manager();
	~Manager();



public:
	static Manager* GetInstance()
	{
		static Manager instance;

		return &instance;
	}

};

