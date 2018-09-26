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

	double			m_fCameraDistance;		// 메인에서 넘겨 받는다
	D3DXVECTOR3		m_vCamRotAngle;			// 메인에서 넘겨 받는다.
	D3DXVECTOR3		m_vBoxPosition;			// 메인에서 넘겨 받는다.
	D3DXVECTOR3		m_vBoxDirection;		// 캐릭터가 향하는 방향. 메인에서 넘겨 받는다.
	bool			m_isFollow;				// 카메라가 캐릭터를 따라 다닐 것인가?
	

public:
	void			Setup();
	void			Update();
	void			SetCameraDistance(double value);
	void			SetCameraRotationAngle(D3DXVECTOR3 Angle);
	D3DXVECTOR3		GetCamPosY();
	void			SetCameraPosY(double posY);
	void			SetBoxPosition(D3DXVECTOR3 position);	
	void			ChangeCameraMode(bool value);

};

