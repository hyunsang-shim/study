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
	D3DXVECTOR3		m_vEye_FIXED;
	D3DXVECTOR3		m_vLookAt_FIXED;	
	D3DXVECTOR3		m_vEye_FOLLOW;
	D3DXVECTOR3		m_vLookAt_FOLLOW;

	double			m_fCameraDistance;		// ���ο��� �Ѱ� �޴´�
	D3DXVECTOR3		m_vCamRotAngle;			// ���ο��� �Ѱ� �޴´�.
	D3DXVECTOR3		m_vBoxPosition;			// ���ο��� �Ѱ� �޴´�.
	D3DXVECTOR3		m_vBoxDirection;		// ĳ���Ͱ� ���ϴ� ����. ���ο��� �Ѱ� �޴´�.
	bool			m_isFollow;				// ī�޶� ĳ���͸� ���� �ٴ� ���ΰ�?
	D3DXMATRIXA16	matProj;



public:
	void			Setup();
	void			Update();
	void			SetCameraDistance(double value);
	void			SetCameraRotationAngle(D3DXVECTOR3 Angle);
	D3DXVECTOR3		GetCamPos();
	void			SetCameraPosY(double posY);
	void			SetBoxPosition(D3DXVECTOR3 position);	
	void			ChangeCameraMode(bool value);
	D3DXVECTOR3		GetCamEye();

};

