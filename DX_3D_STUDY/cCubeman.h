#pragma once
#include "cCharacter.h"

class cCubeNode;

class cCubeman :
	public cCharacter
{
public:
	cCubeman();
	virtual ~cCubeman();


protected :
	cCubeNode*				m_pRoot;
public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

