#include "stdafx.h"
#include "cScenePlayGame.h"
#include "iButtonDelegate.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cFrame.h"
#include "cAseLoader.h"
#include "cSkinnedMesh.h"

cScenePlayGame::cScenePlayGame()
	:m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pButtonDelegate(NULL)
	, m_pAseRoot(NULL)
	, m_pSkinnedMesh(NULL)
{
}

cScenePlayGame::~cScenePlayGame()
{
	if (!m_vecAseBackgriund.empty())
	{
		for (auto p : m_vecAseBackgriund)
			SAFE_DELETE(p);
	}

	SAFE_DELETE(m_pGrid);
}

void cScenePlayGame::Setup(iButtonDelegate* dele)
{
	m_pButtonDelegate = dele;
	m_pGrid = new cGrid;
	m_pGrid->Setup(30, 1);	

	m_pSkinnedMesh = dele->GetSkinnedMesh();

	m_pCamera = dele->GetCamera();
	m_pCamera->Setup();

	std::string sFolder = "ase/";
	cAseLoader AseLoader;
	m_pAseRoot = AseLoader.Load(sFolder, std::string("bil.ASE"));

	
}

void cScenePlayGame::Update()
{
	if (g_pInputManager->GetKeyDownOnce(VK_ESCAPE))
	{
		m_pButtonDelegate->Menu();
	}

	if (m_pCamera)
		m_pCamera->Update();

	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();

	int nKey = (int)(GetTickCount() * 4.8f) % (3200 - 640) + 640;
	
	//D3DXMATRIXA16 matR;
	//D3DXMatrixRotationX(&matR, D3DXToRadian(-90));
	if (m_pAseRoot)
		m_pAseRoot->Update(NULL, nKey);

	
}

void cScenePlayGame::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	if (m_pGrid)
		m_pGrid->Render();

	if (m_pAseRoot)
		m_pAseRoot->Render();

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Render(&matWorld);

}

void cScenePlayGame::Exit()
{
	
}
