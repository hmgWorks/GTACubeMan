#pragma once
#include "iButtonDelegate.h"
class cCamera;

class cMainGame
	:public cObject, public iButtonDelegate
{	
private:	
	std::map<SCENE, iSceneBase*> m_mapScene;

	iSceneBase*	m_pCurrentScene;
	cCamera*	m_pCamera;


public://get/set
	cCamera* GetCamera(){ return m_pCamera; }

public:
	cMainGame();
	virtual ~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void ChangeScene(SCENE scene, cCamera* camera = NULL);

	void OnClick(cObject* pSender) override;
};

