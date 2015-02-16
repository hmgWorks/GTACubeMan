#include "stdafx.h"
#include "cMainGame.h"
#include "cSceneIntro.h"

cMainGame::cMainGame()
	:m_pCurrentScene(NULL)
{
}

cMainGame::~cMainGame()
{
	for (auto p : m_vecScene)
	{
		SAFE_DELETE(p);
	}

}

void cMainGame::Setup()
{
	m_vecScene.resize(SCENE::SCENE_MAX);
	m_vecScene[SCENE::SCENE_INTRO] = new cSceneIntro;

	m_pCurrentScene = m_vecScene[SCENE::SCENE_INTRO];
	m_pCurrentScene->Setup();
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
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	m_pCurrentScene->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	
	}
}