#pragma once

class cMouseController
{
private:

	POINT m_ptMousePos;
	POINT m_ptPrevMousePos;

	float m_fDist;
	bool m_isLButtonDown;
	bool m_isRButtonDown;

public:
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Update();
	void Render();

	POINT GetMousePos();
	POINT GetPrevMousePos();
	float GetDist();
	bool GetLButtonDown();
	bool GetRButtonDown();

	cMouseController();
	~cMouseController();
};

