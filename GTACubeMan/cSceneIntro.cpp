#include "stdafx.h"
#include "cSceneIntro.h"


cSceneIntro::cSceneIntro()
	:m_pSprite(NULL)
	, m_pTextureBackground(NULL)
{
}

cSceneIntro::~cSceneIntro()
{
	SAFE_RELEASE(m_pTextureBackground);
	SAFE_RELEASE(m_pSprite);
}

void cSceneIntro::Setup()
{
	m_pTextureBackground = g_pTextureManager->GetTexture("image/INTRO_BACKGROUND_TOWN.jpg");
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);	
}

void cSceneIntro::Update()
{

}

void cSceneIntro::Render()
{
	D3DVIEWPORT9 v;
	g_pD3DDevice->GetViewport(&v);
	RECT rc;
	SetRect(&rc, 0, 0, (int)v.Width, (int)v.Height);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->Draw(m_pTextureBackground, NULL, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255, 255, 255));
	m_pSprite->End();
}
