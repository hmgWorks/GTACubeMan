#pragma once

__interface iButtonDelegate;

__interface iSceneBase
{
public:
	void Setup(iButtonDelegate* dele);
	void Update();
	void Render();
	void Exit();//ui ��ü�� ���� �ʴ� �κ��� �־ exit()���� ��ü�� ����� �ȉ�.
};

