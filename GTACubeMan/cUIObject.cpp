#include "StdAfx.h"
#include "cUIObject.h"


cUIObject::cUIObject(LPD3DXSPRITE pSprite)
	: m_pParent(NULL)
	, m_vPosition(0, 0, 0)
	, m_vScale(1, 1, 1)
	, m_pSprite(pSprite)
{
}

cUIObject::~cUIObject(void)
{
}

void cUIObject::AddChild( cUIObject* pChild )
{
	pChild->AddRef();
	pChild->m_pParent = this;
	m_vecChild.push_back(pChild);
}

void cUIObject::Update()
{
	D3DXMATRIXA16 matS, matT;
	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matT;
	if(m_pParent)
	{
		m_matWorld = m_matWorld * m_pParent->m_matWorld;
	}

	for (auto pChild : m_vecChild)
	{
		pChild->Update();
	}
}

void cUIObject::Render()
{
	for (auto pChild : m_vecChild)
	{
		pChild->Render();
	}
}

void cUIObject::Destroy()
{
	for (auto pChild : m_vecChild)
	{
		pChild->Destroy();
	}
	
	Release();
}
