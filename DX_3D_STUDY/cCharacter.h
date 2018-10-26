#pragma once
class cCharacter : public cObject
{
public:
	cCharacter();
	virtual ~cCharacter(void);


protected:
	float					m_fRotY;
	D3DXVECTOR3				m_vDirection;
	D3DXVECTOR3				m_vPosition;
	D3DXMATRIXA16			m_matWorld;


public:
	virtual void			Setup();
	virtual void			Update();
	virtual void			Render();
	virtual void			SetPos(D3DXVECTOR3 pos);
	virtual D3DXVECTOR3&	GetPosition();
	virtual D3DXMATRIXA16*	GetTransform();
};

