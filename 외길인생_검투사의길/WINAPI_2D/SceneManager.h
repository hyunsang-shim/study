#pragma once
#include "cManager.h"
#include <vector>

class SceneManager : public cManager
{
public:
	SceneManager();
	~SceneManager();
	void UnLoadScene();
	void LoadScene(int destSceneidx);
	void DrawScene(HDC hdc);
	void ChangeScene(int destSceneidx);
	void DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src);
	void DrawSpriteImage(HDC destDC, int startX, int startY, HBITMAP src, int frameNumber);
	void DrawToFront(HDC destDC, HDC srcDC);
	std::vector<HBITMAP> resources;

private:	

};

