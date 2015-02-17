#include "StdAfx.h"
#include "cCamera.h"

#include "cMouseController.h"

cCamera::cCamera(void)
	: m_vEye(0, 0, -10)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_fAngleX(0.0f)
	, m_fAngleY(0.0f)
	, m_pMouseController(NULL)
{
}


cCamera::~cCamera(void)
{
	SAFE_DELETE(m_pMouseController);
}

void cCamera::Setup()
{
	//D3DXMATRIXA16 matView;	멤버로 가지고 있는게 좋을듯
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);

	//D3DVIEWPORT9 vp;		//멤버로 가지고 있는게 좋을듯
	g_pD3DDevice->GetViewport(&m_VIEWPORT);

	//D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DXToRadian(45), m_VIEWPORT.Width / (float)m_VIEWPORT.Height, 1.0f, 10000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

	//setup laser line (have 2 vertices to draw line) this is only for your eyes to check
	SetupLaserDirection();
}

void cCamera::Update()
{
	//move and rotate camera
	UpdateCameraPosAngle();

	//update laser's origin and direction
	//this should give you laser position in terms of world matrix
	UpdateLaserOriginDirection();


}

void cCamera::UpdateCameraPosAngle()
{
	m_vEye = D3DXVECTOR3(0, 0, - (m_pMouseController->GetDist() ) );		//get scroll dist from cMouseController

	//get mouse position from cMouseController
	//항상 curr는 업데이트됨
	POINT ptCurrMouse = m_pMouseController->GetMousePos();
	//POINT ptPrevMouse = m_pMCont->GetPrevMousePos();
	//이거 추후 수정해야함...
	//for now winproc 일부는 cCamera에 어쩔수 없이 두기로...

	//calc mouse movement & control sensitivity
	float fDeltaX = (ptCurrMouse.x - m_ptPrevMouse.x) / 100.f;
	float fDeltaY = (ptCurrMouse.y - m_ptPrevMouse.y) / 100.f;

	if (m_pMouseController->GetRButtonDown() == true)
	{
		//apply mousemovement to camera angle
		m_fAngleX += fDeltaY;
		m_fAngleY += fDeltaX;

		//★이거 안하면 카메라 계속 돔
		m_ptPrevMouse = ptCurrMouse;
	}

	//limit camera angle
	if (m_fAngleX >= D3DX_PI / 2.f - 0.0001f)
		m_fAngleX = D3DX_PI / 2.f - 0.0001f;

	if (m_fAngleX <= -D3DX_PI / 2.f + 0.0001f)
		m_fAngleX = -D3DX_PI / 2.f + 0.0001f;


	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fAngleX);
	D3DXMatrixRotationY(&matRotY, m_fAngleY);

	//update eye (rotate)
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRotX);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRotY);


	D3DXVECTOR3 vTarget = D3DXVECTOR3(10, 10, -10);
	m_vEye += vTarget;
	m_vLookAt = vTarget;
	//if (m_pMC)	//get player position data using a pointer (from cMainChararacter)
	//{
	//	D3DXVECTOR3 vTarget = m_pMC->GetCharacterPos();
	//	m_vEye += vTarget;	//camera pos = camera vector + player pos vector
	//	m_vLookAt = vTarget;	//this should always look at player
	//}


	//D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);


}

void cCamera::UpdateLaserOriginDirection()
{

	//get mouse position
	POINT pMousePos = m_pMouseController->GetMousePos();

	//calculate laser direction and position (viewport상의 수치임)
	//g_pD3DDevice->GetViewport(&m_VIEWPORT);
	//D3DXMATRIXA16 matProj;
	//g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &m_matProj);
	//이미 멤버 변수에 계산하고 있음

	float fX, fY;
	fX = (((2.0f * pMousePos.x) / m_VIEWPORT.Width) - 1.0f) / m_matProj(0, 0);
	fY = (((-2.0f * pMousePos.y) / m_VIEWPORT.Height) + 1.0f) / m_matProj(1, 1);

	//viewport상의 레이져 수치를 이렇게 구할 수 있음
	m_vLaserOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vLaserDirection = D3DXVECTOR3(fX, fY, 1.0f);


	//이제 월드매트릭스로 변환해야함
	//rendering 기본 pipeline중... LOCAL WORLD VIEW

	//get inverse matrix view
	D3DXMATRIXA16 matInverseMatView;
	D3DXMatrixInverse(&matInverseMatView, NULL, &m_matView);		//probably don't need determinant (set as NULL)

	//레이져의 원점을 변환
	D3DXVec3TransformCoord(&m_vLaserOrigin, &m_vLaserOrigin, &matInverseMatView);

	//레이져의 방향(direction)을 변환
	D3DXVec3TransformNormal(&m_vLaserDirection, &m_vLaserDirection, &matInverseMatView);

	//normalize
	D3DXVec3Normalize(&m_vLaserDirection, &m_vLaserDirection);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONDOWN:
	{
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
	}
	break;
	}
}

void cCamera::SetMouseControllerPtr(cMouseController* targetmouse)
{
	m_pMouseController = targetmouse;
}


void cCamera::SetupLaserDirection()
{

	//set color
	m_PCVertex.c = D3DCOLOR_XRGB(255, 0, 255);

	//set two positions
	//start at 0, 0, 0

	//push back two vertices
	m_PCVertex.p = D3DXVECTOR3(0, 0, 0);
	m_ST_PCVertexContainer.push_back(m_PCVertex);

	m_PCVertex.p = D3DXVECTOR3(20, 20, 20);
	m_ST_PCVertexContainer.push_back(m_PCVertex);

}

void cCamera::RenderLaserDirection()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);// don't use lighting with line
	D3DXMATRIXA16 matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	g_pD3DDevice->SetTexture(0, 0);	//no texture for lines
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matIdentity);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_ST_PCVertexContainer.size() / 2, &m_ST_PCVertexContainer[0], sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);// turn lighting back on	
}

void cCamera::UpdateLaserDirection()
{
	m_ST_PCVertexContainer[0].p = m_vLaserOrigin;
	m_ST_PCVertexContainer[1].p = m_vLaserDirection;

	//this is only for testing
	//m_ST_PCVertexContainer[0].p = D3DXVECTOR3(0, 0, 0);
	//m_vLaserOrigin = D3DXVECTOR3(0, 0, 0);
}

D3DXVECTOR3 cCamera::GetLaserOrigin()
{
	return m_vLaserOrigin;
}

D3DXVECTOR3 cCamera::GetLaserDir()
{
	return m_vLaserDirection;
}