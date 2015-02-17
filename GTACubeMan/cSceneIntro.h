#pragma once
//#include "iSceneBase.h"

/*
	게임을 실행하면 바로 뜨는 Scene
	게임을 시작할 수 있는 버튼과 게임을 종료 할 수 있는 버튼이 있다.
	버튼 조작은 마우스 클릭.
	게임중 intro로 올 수 있다.

	모든 scene는 interface 'iSceneBase'를 상속 받아 구현해야 한다.

	추가로 'new game', 'continue game'
*/
class cUIObject;
__interface iButtonDelegate;

class cSceneIntro
	:public iSceneBase
{
private:
	LPD3DXSPRITE	m_pSprite;	
	cUIObject*		m_pUIRoot;

public:
	cSceneIntro();
	virtual ~cSceneIntro();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

