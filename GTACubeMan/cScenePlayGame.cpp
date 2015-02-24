#include "stdafx.h"
#include "cScenePlayGame.h"
#include "iButtonDelegate.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cSkinnedMesh.h"
#include "cGroup.h"
#include "cObjLoader.h"

cScenePlayGame::cScenePlayGame()
	:m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pButtonDelegate(NULL)
	, m_pSkinnedMesh(NULL)
{
}

cScenePlayGame::~cScenePlayGame()
{
	if (!m_vecGroup.empty())
	{
		for (auto p : m_vecGroup)
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
	
	cObjLoader ObjLoader;
	ObjLoader.Load(m_vecGroup, std::string("obj/"), std::string("road.obj"));

	
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
	
}

void cScenePlayGame::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	if (m_pGrid)
		m_pGrid->Render();

	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Render(&matWorld);

	for (auto p : m_vecGroup)
		p->Render();

}

void cScenePlayGame::Exit()
{
	
}
