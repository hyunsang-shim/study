#pragma once

#include "cCharacter.h"

class cSkinnedMesh;
class cOBB;
//class iMap;

class cZealot
{
public:
	cZealot();
	virtual ~cZealot();
	void			Setup();
	void			Setup(D3DXVECTOR3 startPos);
	void			Update();
	void			Render(D3DCOLOR c = D3DCOLOR_XRGB(120, 120, 120));
	cOBB*			GetOBB();

private:

	cSkinnedMesh*			m_pSkinnedMesh;
	cOBB*					m_pOBB;
	SYNTHESIZE_ADD_REF(cCharacter*, m_pCharacterController, CharacterController);

};