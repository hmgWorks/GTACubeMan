#include "stdafx.h"
#include "cSceneInGame.h"
#include "iButtonDelegate.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cMouseController.h"

cSceneInGame::cSceneInGame()
	:m_pGrid(NULL)
	, m_pCamera(NULL)
{
}

cSceneInGame::~cSceneInGame()
{
}

void cSceneInGame::Setup(iButtonDelegate* dele, cCamera* camera)
{
	m_pGrid = new cGrid;
	m_pGrid->Setup(30, 1);	
	
	m_pCamera = camera;
	m_pCamera->Setup();
	
}

void cSceneInGame::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
}

void cSceneInGame::Render()
{
	if (m_pGrid)
		m_pGrid->Render();
}

void cSceneInGame::Exit()
{
	SAFE_DELETE(m_pGrid);
}
