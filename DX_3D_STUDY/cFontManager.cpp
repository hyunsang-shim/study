#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(eFontType e)
{
	if (m_mapFont.find(e) != m_mapFont.end())
	{
		return m_mapFont[e];


	}

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	if (e == E_DEFAULT)
	{
		fd.Height = 50;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		// �ý��� ��Ʈ�� ��� �� ���
		//strcpy_s(fd.FaceName, "����ü");

		
		strcpy_s(fd.FaceName, "����ü.ttf");
		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);

		return m_mapFont[e];
		
	}

	if (e == E_QUEST)
	{
		fd.Height = 50;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;

		// �ý��� ��Ʈ�� ��� �� ���
		//strcpy_s(fd.FaceName, "����ü");

		AddFontResource("font/umberto.ttf");
		strcpy_s(fd.FaceName, "umberto.ttf");
		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);

		return m_mapFont[e];

	}

	return LPD3DXFONT();
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
}
