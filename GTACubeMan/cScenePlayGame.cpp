#include "stdafx.h"
#include "cScenePlayGame.h"
#include "iButtonDelegate.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cFrame.h"
#include "cAseLoader.h"

cScenePlayGame::cScenePlayGame()
	:m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pButtonDelegate(NULL)
	, m_pAseRoot(NULL)
{
}

cScenePlayGame::~cScenePlayGame()
{
	SAFE_DELETE(m_pGrid);
}

void cScenePlayGame::Setup(iButtonDelegate* dele)
{
	m_pButtonDelegate = dele;
	m_pGrid = new cGrid;
	m_pGrid->Setup(30, 1);	
	
	m_pCamera = dele->GetCamera();
	m_pCamera->Setup();

	std::string sFolder = "ase/";
	cAseLoader AseLoader;
	m_pAseRoot = AseLoader.Load(sFolder, std::string("House_01.ASE"));
	
}

void cScenePlayGame::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
	if (g_pInputManager->GetKeyDownOnce(VK_ESCAPE))
	{
		m_pButtonDelegate->MenuSetting();
	}

	int nKey = (int)(GetTickCount() * 4.8f) % (3200 - 640) + 640;
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationX(&matR, D3DXToRadian(-90));
	if (m_pAseRoot)
		m_pAseRoot->Update(&matR, nKey);
}

void cScenePlayGame::Render()
{
	if (m_pGrid)
		m_pGrid->Render();

	if (m_pAseRoot)
		m_pAseRoot->Render();
}

void cScenePlayGame::Exit()
{
	
}
