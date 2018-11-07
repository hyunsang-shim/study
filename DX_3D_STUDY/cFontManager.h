#pragma once

#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{
public:
	/*cFontManager();
	~cFontManager();*/
	enum eFontType {
		E_DEFAULT,
		E_QUEST,
		E_MAX,

	};

private:
	SINGLETONE(cFontManager);
	map<eFontType, LPD3DXFONT> m_mapFont;

public:
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();

};
