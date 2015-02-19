#include "stdafx.h"
#include "cSceneMenu.h"
#include "cUIImageView.h"
#include "cUIImageButton.h"

cSceneMenu::cSceneMenu()
	:m_pSprite(NULL)
	, m_pUIRoot(NULL)
{
}


cSceneMenu::~cSceneMenu()
{
	if (m_pUIRoot)
		m_pUIRoot->Destroy();

	SAFE_RELEASE(m_pSprite);
}

void cSceneMenu::Setup(iButtonDelegate* dele)
{
	//D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	//cUIImageView* Background = new cUIImageView(m_pSprite);
	//Background->SetPosition({ 0, 0, 0 });
	//Background->SetTextureFilename(std::string("image/INTRO_BACKGROUND_TOWN.jpg"));
	//m_pUIRoot = Background;

	//cUIImageButton* ButtonStartGame = new cUIImageButton(m_pSprite);
	//ButtonStartGame->SetTag(SCENE::SCENE_NEW_PLAY);
	//ButtonStartGame->SetDelegate(dele);
	//ButtonStartGame->Setup("image/INTRO_BUTTON_STARTGAME.png", "image/INTRO_BUTTON_STARTGAMEOVER.png", "image/INTRO_BUTTON_STARTGAMECLICK.png");
	//ButtonStartGame->SetPosition({ 500, 500, 0 });
	//m_pUIRoot->AddChild(ButtonStartGame);
	//SAFE_RELEASE(ButtonStartGame);

	//cUIImageButton* ButtonExitGame = new cUIImageButton(m_pSprite);
	//ButtonExitGame->SetTag(SCENE::SCENE_END);
	//ButtonExitGame->SetDelegate(dele);
	//ButtonExitGame->Setup("image/INTRO_BUTTON_EXITGAME.png", "image/INTRO_BUTTON_EXITGAMEOVER.png", "image/INTRO_BUTTON_EXITGAMECLICK.png");
	//ButtonExitGame->SetPosition({ 500, 600, 0 });
	//m_pUIRoot->AddChild(ButtonExitGame);
	//SAFE_RELEASE(ButtonExitGame);
}

void cSceneMenu::Update()
{
	/*if (m_pUIRoot)
		m_pUIRoot->Update();*/
}

void cSceneMenu::Render()
{
	//if (m_pUIRoot)
	//	m_pUIRoot->Render();
}

void cSceneMenu::Exit()
{

}

