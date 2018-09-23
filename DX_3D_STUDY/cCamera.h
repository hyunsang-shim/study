#pragma once
class cCamera
{
public:
	cCamera();
	~cCamera();

private:

	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	double			m_fCameraDistance;		// ���ο��� �Ѱ� �޴´�
	D3DXVECTOR3		m_vCamRotAngle;			// ���ο��� �Ѱ� �޴´�.
	D3DXVECTOR3		m_vBoxPosition;			// ���ο��� �Ѱ� �޴´�.

public:
	void			Setup();
	void			Update();
	void			SetCameraDistance(double value);
	void			SetCameraRotationAngle(D3DXVECTOR3 Angle);
	D3DXVECTOR3		GetCamPosY();
	void			SetCameraPosY(double posY);
	void			SetBoxPosition(D3DXVECTOR3 position);
	
};

