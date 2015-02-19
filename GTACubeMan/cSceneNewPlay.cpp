#include "stdafx.h"
#include "cSceneNewPlay.h"
#include "cUIImageView.h"
#include "cUIImageButton.h"

cSceneNewPlay::cSceneNewPlay()
	:m_pSprite(NULL)
	, m_pUIRoot(NULL)
{
}


cSceneNewPlay::~cSceneNewPlay()
{
	if (m_pUIRoot)
		m_pUIRoot->Destroy();

	SAFE_RELEASE(m_pSprite);
}

void cSceneNewPlay::Setup(iButtonDelegate* dele)
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	cUIImageView* Background = new cUIImageView(m_pSprite);
	Background->SetPosition({ 200, 100, 0 });
	Background->SetTextureFilename(std::string("image/INTRO_BACKGROUND_PEOPLE.jpg"));
	m_pUIRoot = Background;

	cUIImageButton* ButtonBack = new cUIImageButton(m_pSprite);
	ButtonBack->SetTag(SCENE::SCENE_INTRO);
	ButtonBack->SetDelegate(dele);
	ButtonBack->Setup("image/NEW_PLAY_BUTTON_BACK.png", "image/NEW_PLAY_BUTTON_BACKOVER.png", "image/NEW_PLAY_BUTTON_BACKCLICK.png");
	ButtonBack->SetPosition({ 000, 500, 0 });
	m_pUIRoot->AddChild(ButtonBack);
	SAFE_RELEASE(ButtonBack);

	cUIImageButton* ButtonStart = new cUIImageButton(m_pSprite);
	ButtonStart->SetTag(SCENE::SCENE_PLAY_GAME);
	ButtonStart->SetDelegate(dele);
	ButtonStart->Setup("image/NEW_PLAY_BUTTON_START.png", "image/NEW_PLAY_BUTTON_STARTOVER.png", "image/NEW_PLAY_BUTTON_STARTCLICK.png");
	ButtonStart->SetPosition({ 300, 500, 0 });
	m_pUIRoot->AddChild(ButtonStart);
	SAFE_RELEASE(ButtonStart);
}

void cSceneNewPlay::Update()
{
	if (m_pUIRoot)
		m_pUIRoot->Update();
}

void cSceneNewPlay::Render()
{
	if (m_pUIRoot)
		m_pUIRoot->Render();
}

void cSceneNewPlay::Exit()
{

}