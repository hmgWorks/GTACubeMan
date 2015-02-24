#pragma once

__interface iButtonDelegate;

__interface iSceneBase
{
public:
	void Setup(iButtonDelegate* dele);
	void Update();
	void Render();
	void Exit();//ui 객체랑 맞지 않는 부분이 있어서 exit()에서 객체를 지우면 안됌.
};

