#pragma once
__interface iButtonDelegate;
class cCamera;

__interface iSceneBase
{
public:
	void Setup(iButtonDelegate* dele, cCamera* camera = NULL);
	void Update();
	void Render();
	void Exit();
};

