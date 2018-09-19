#pragma once
class cCamera
{
public:
	cCamera();
	~cCamera();

private:

	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vUp;

public:
	void Setup();
	void Update();
};

