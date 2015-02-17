#pragma once
__interface iSceneBase;

class cMainGame
	:public cObject
{
private:
	enum SCENE
	{
		SCENE_INTRO, SCENE_TUTO, SCENE_INGAME, SCENE_END, SCENE_MAX
	};
	std::vector<iSceneBase*> m_vecScene;
	iSceneBase* m_pCurrentScene;

public:
	cMainGame();
	virtual ~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void ChangeScene(SCENE scene);
};

