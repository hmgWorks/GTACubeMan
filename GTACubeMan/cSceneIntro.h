#pragma once
//#include "iSceneBase.h"

/*
	������ �����ϸ� �ٷ� �ߴ� Scene
	������ ������ �� �ִ� ��ư�� ������ ���� �� �� �ִ� ��ư�� �ִ�.
	��ư ������ ���콺 Ŭ��.
	������ intro�� �� �� �ִ�.

	��� scene�� interface 'iSceneBase'�� ��� �޾� �����ؾ� �Ѵ�.

	�߰��� 'new game', 'continue game'
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

