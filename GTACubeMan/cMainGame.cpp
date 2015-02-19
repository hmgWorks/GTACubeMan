#include "stdafx.h"
#include "cMainGame.h"
#include "cSceneIntro.h"
#include "cSceneNewPlay.h"
#include "cSceneSelectPlayData.h"
#include "cScenePlayGame.h"
#include "cSceneEnd.h"
#include "cSceneMenu.h"
#include "cCamera.h"

cMainGame::cMainGame()
	:m_pCurrentScene(NULL)
	, m_pCamera(NULL)
{
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	for (auto p : m_mapScene)
	{
		SAFE_DELETE(p.second);
	}

}

void cMainGame::Setup()
{		
	m_mapScene[SCENE::SCENE_INTRO]				= new cSceneIntro;
	m_mapScene[SCENE::SCENE_NEW_PLAY]			= new cSceneNewPlay;
	m_mapScene[SCENE::SCENE_SELECT_PLAY_DATA]	= new cSceneSelectPlayData;
	m_mapScene[SCENE::SCENE_PLAY_GAME]			= new cScenePlayGame;
	m_mapScene[SCENE::SCENE_END]				= new cSceneEnd;
	m_mapScene[SCENE::SCENE_MENU]				= new cSceneMenu;

	m_pCurrentScene = m_mapScene[SCENE::SCENE_INTRO];
	m_pCurrentScene->Setup(this);

	m_pCamera = new cCamera;
	m_pCamera->Setup();
}

void cMainGame::Update()
{
	m_pCurrentScene->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(33, 40, 48),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	m_pCurrentScene->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_pInputManager->GetInstance())
			g_pInputManager->GetInstance()->WndProc(hWnd, message, wParam, lParam);
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	
	default:
		break;
	}	
}

void cMainGame::ChangeScene(SCENE scene)
{
	if (m_mapScene[scene] != m_pCurrentScene)
	{		
		m_pCurrentScene->Exit();
		m_pCurrentScene = m_mapScene[scene];
		m_pCurrentScene->Setup(this);		
	}
}

void cMainGame::OnClick(cObject* pSender)
{
	SCENE nextScene = (SCENE)pSender->GetTag();
	switch (nextScene)
	{
	case SCENE::SCENE_INTRO:
		ChangeScene(nextScene);
		break;
	case SCENE::SCENE_NEW_PLAY:
		ChangeScene(nextScene);
		break;
	case SCENE::SCENE_SELECT_PLAY_DATA:
		ChangeScene(nextScene);
		break;
	case SCENE::SCENE_PLAY_GAME:
		ChangeScene(nextScene);
		break;
	case SCENE::SCENE_END:
		::DestroyWindow(g_hWnd);
		break;	
	case SCENE::SCENE_MENU:
		ChangeScene(nextScene);
		break;
	}
}

void cMainGame::MenuSetting()
{
	ChangeScene(SCENE::SCENE_MENU);
}