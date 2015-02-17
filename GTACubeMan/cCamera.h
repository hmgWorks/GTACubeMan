#pragma once

class cMouseController;

class cCamera
{
private:
	std::vector<ST_PC_VERTEX> m_ST_PCVertexContainer;
	ST_PC_VERTEX m_PCVertex;

	D3DXMATRIXA16 m_matView;
	D3DVIEWPORT9 m_VIEWPORT;
	D3DXMATRIXA16 m_matLaser;
	D3DXVECTOR3 m_vLaserOrigin;
	D3DXVECTOR3 m_vLaserDirection;
	D3DXMATRIXA16 m_matProj;

	cMouseController* m_pMouseController;		//this is a connector(pointer) to cMouseController (camera gotta be controlled by mouse)
	
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	POINT		m_ptPrevMouse;
	float			m_fAngleX;
	float			m_fAngleY;

public:
	cCamera(void);
	~cCamera(void);

	void SetMouseControllerPtr(cMouseController* targetmouse);
	
	void Setup();
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void UpdateCameraPosAngle();
	void UpdateLaserOriginDirection();
	void RenderLaserDirection();
	void SetupLaserDirection();		//this is only for your eyes to check (setting up two vertices to draw primitive)
	void UpdateLaserDirection();

	D3DXVECTOR3 GetLaserOrigin();
	D3DXVECTOR3 GetLaserDir();
};

