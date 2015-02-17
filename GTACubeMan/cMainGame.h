#pragma once
#include "iButtonDelegate.h"
class cMouseController;


class cMainGame
	:public cObject, public iButtonDelegate
{	
private:	
	std::vector<iSceneBase*> m_vecScene;
	iSceneBase* m_pCurrentScene;
	cMouseController*	m_pMouseController;
public:
	cMainGame();
	virtual ~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void ChangeScene(SCENE scene);

	void OnClick(cObject* pSender) override;
};

