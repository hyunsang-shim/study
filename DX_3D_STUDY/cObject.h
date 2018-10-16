#pragma once
/* °­»ç´Ô ASE ·Î´õ*/
class cObject
{
public:
	cObject();
	~cObject();

protected:
	ULONG m_ulRefCount;
public :
	virtual void AddRef();
	virtual void Release();

};

