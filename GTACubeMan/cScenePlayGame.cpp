#include "stdafx.h"
#include "cScenePlayGame.h"
#include "iButtonDelegate.h"
#include "cGrid.h"
#include "cCamera.h"

cScenePlayGame::cScenePlayGame()
	:m_pGrid(NULL)
	, m_pCamera(NULL)
{
}

cScenePlayGame::~cScenePlayGame()
{
}

void cScenePlayGame::Setup(iButtonDelegate* dele)
{
	m_pGrid = new cGrid;
	m_pGrid->Setup(30, 1);	
	
	m_pCamera = dele->GetCamera();
	m_pCamera->Setup();
	
}

void cScenePlayGame::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
}

void cScenePlayGame::Render()
{
	if (m_pGrid)
		m_pGrid->Render();
}

void cScenePlayGame::Exit()
{
	SAFE_DELETE(m_pGrid);
}
