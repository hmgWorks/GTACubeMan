#pragma once
#include "iButtonDelegate.h"

class cCamera;
class cSkinnedMesh;

class cMainGame
	:public cObject, public iButtonDelegate
{	
private:	
	std::map<SCENE, iSceneBase*> m_mapScene;

	iSceneBase*	m_pCurrentScene;
	cCamera*	m_pCamera;
	cSkinnedMesh* m_pSkinnedMesh;

public:
	cMainGame();
	virtual ~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void ChangeScene(SCENE scene);

	//iButtonDelegate
	void OnClick(cObject* pSender) override;
	cCamera* GetCamera() override;
	cSkinnedMesh* GetSkinnedMesh() override;
	//void InitPlayer() override;
	void CreatePlayer();
	void Menu() override;
};

