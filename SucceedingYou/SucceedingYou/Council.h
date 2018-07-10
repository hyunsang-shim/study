#pragma once
// 싱글톤 예제 활용.
// 싱글톤 기본형 : 강사님 작성

class cCouncil {
public:
	cCouncil();
	~cCouncil();

	static cCouncil *GetInstance()
	{
		static cCouncil instance;
		return &instance;
	}

	//개인 코드에 따라 작성

};

#define g_Council cCouncil::GetInstance()

