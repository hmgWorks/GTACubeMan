#pragma once
#include "iSceneBase.h"

/*
	������ �����ϸ� �ٷ� �ߴ� Scene
	������ ������ �� �ִ� ��ư�� ������ ���� �� �� �ִ� ��ư�� �ִ�.
	��ư ������ ���콺 Ŭ��.
	������ intro�� �� �� �ִ�.

	��� scene�� interface 'iSceneBase'�� ��� �޾� �����ؾ� �Ѵ�.

	�߰��� 'new game', 'continue game'
*/
class cUIImageButton;

class cSceneIntro :
	public iSceneBase
{
private:
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTextureBackground;
	cUIImageButton* m_pButtonStartGame;
	cUIImageButton* m_pButtonExitGame;

public:
	cSceneIntro();
	virtual ~cSceneIntro();

	void Setup() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

