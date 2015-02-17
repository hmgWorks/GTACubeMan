#include "stdafx.h"
#include "cMouseController.h"

cMouseController::cMouseController()
	: m_fDist(10.0f),
	m_isLButtonDown(false),
	m_isRButtonDown(false)
{
	m_ptMousePos.x = 0;
	m_ptMousePos.y = 0;
	m_ptPrevMousePos.x = 0;
	m_ptPrevMousePos.y = 0;
}


cMouseController::~cMouseController()
{

}

void cMouseController::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLButtonDown = true;
	}
	break;
	case WM_RBUTTONDOWN:
	{
		m_ptPrevMousePos.x = LOWORD(lParam);
		m_ptPrevMousePos.y = HIWORD(lParam);
		m_isRButtonDown = true;
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}
	break;
	case WM_RBUTTONUP:
	{
		m_isRButtonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		m_ptMousePos.x = LOWORD(lParam);
		m_ptMousePos.y = HIWORD(lParam);
	}
	break;
	case WM_MOUSEWHEEL:
	{
		m_fDist -= GET_WHEEL_DELTA_WPARAM(wParam) / 100.f;
		if (m_fDist < 0.1f)
			m_fDist = 0.1f;
	}
	break;
	}
}

POINT cMouseController::GetMousePos()
{
	return m_ptMousePos;
}

POINT cMouseController::GetPrevMousePos()
{
	return m_ptPrevMousePos;
}

float cMouseController::GetDist()
{
	return m_fDist;
}

bool cMouseController::GetLButtonDown()
{
	return m_isLButtonDown;
}

bool cMouseController::GetRButtonDown()
{
	return m_isRButtonDown;
}

void cMouseController::Update()
{
	//이건 지금은 사용 안하는중
	//나중에 inventory 짤때 필요할듯
}
