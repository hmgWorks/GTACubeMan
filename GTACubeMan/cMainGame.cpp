#include "stdafx.h"
#include "cMainGame.h"
#include "cSceneIntro.h"
#include "cSceneNewPlay.h"
#include "cSceneSelectPlayData.h"
#include "cScenePlayGame.h"
#include "cSceneEnd.h"
#include "cSceneMenu.h"
#include "cCamera.h"
#include "cSkinnedMesh.h"
#include <thread>

cMainGame::cMainGame()
	:m_pCurrentScene(NULL)
	, m_pCamera(NULL)
	, m_pSkinnedMesh(NULL)
{
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pSkinnedMesh);
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
	g_pTimeManager->Update();

	if (m_pCurrentScene)
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

	if (m_pCurrentScene)
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
		CreatePlayer();
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

void cMainGame::Menu()
{
	ChangeScene(SCENE::SCENE_MENU);
}

cCamera* cMainGame::GetCamera()
{ 
	return m_pCamera; 
}

cSkinnedMesh* cMainGame::GetSkinnedMesh()
{
	return m_pSkinnedMesh; 
}


#pragma region 미완 쓰레드 변경 해야함
//void cMainGame::InitPlayer()
//{
//	std::thread t(&cMainGame::CreatePlayer, this);
//	t.join();
//}

void cMainGame::CreatePlayer()
{
	m_pSkinnedMesh = new cSkinnedMesh;
	m_pSkinnedMesh->Setup(std::string("xfile/"), std::string("zealot.X"));
	m_pSkinnedMesh->SetAnimationLoop(0, false);
	m_pSkinnedMesh->SetAnimationLoop(1, false);
	m_pSkinnedMesh->SetAnimationLoop(2, false);
	m_pSkinnedMesh->SetAnimationLoop(3, true);
	m_pSkinnedMesh->SetAnimationLoop(4, true);
	m_pSkinnedMesh->SetAnimationIndex(4);
}
#pragma endregion
