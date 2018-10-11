#pragma once
class cASE_Char
{
public:
	cASE_Char();
	~cASE_Char();
	void Setup();
	void Update();
	void Render();

private:
	vector<ASE_Obj>					ASEOBJ;
};

