#pragma once
#include "iSceneBase.h"


class cSceneIntro :
	public iSceneBase
{
private:
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pTextureBackground;
public:
	cSceneIntro();
	virtual ~cSceneIntro();

	void Setup() override;
	void Update() override;
	void Render() override;
};

