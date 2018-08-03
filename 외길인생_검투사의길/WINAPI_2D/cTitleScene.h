#pragma once
#include "SceneManager.h"

class cTitleScene : public SceneManager
{
public:
	cTitleScene();
	int GetCurSelectorFrame();
	void SetCurSelectorFrame(int frame);
	~cTitleScene();

private:
	int curSelectorFrame = 0;
};

