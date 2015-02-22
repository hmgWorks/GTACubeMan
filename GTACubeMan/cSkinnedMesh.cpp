#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"
#include "cAnimationSet.h"

cSkinnedMesh::cSkinnedMesh(void)
	: m_pRootFrame(NULL)
	, m_fAnimationBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimationBlending(false)
	, m_nCurrentAnimation(0)
{
}


cSkinnedMesh::~cSkinnedMesh(void)
{
	if(m_pRootFrame)
	{
		cAllocateHierarchy Alloc;
		D3DXFrameDestroy(m_pRootFrame, &Alloc);
	}
}

void cSkinnedMesh::Setup( std::string sFolder, std::string sFile )
{
	cAllocateHierarchy Alloc;
	Alloc.SetFolder("xfile/");
	D3DXLoadMeshHierarchyFromX(
		(sFolder + sFile).c_str(), 
		D3DXMESH_MANAGED, 
		g_pD3DDevice, 
		&Alloc,
		NULL,
		&m_pRootFrame,
		&m_pAnimControl);

	UINT uiNumAnim = m_pAnimControl->GetNumAnimationSets();

	for (UINT i = 0; i < uiNumAnim; ++i)
	{
		cAnimationSet* pAnimSet = new cAnimationSet;
		LPD3DXANIMATIONSET pAS = NULL;
		m_pAnimControl->GetAnimationSet(i, &pAS);
		pAnimSet->SetAnimationSet(pAS);
		SAFE_RELEASE(pAS);
		pAnimSet->SetIndex(m_vecAnimationSet.size());
		m_vecAnimationSet.push_back(pAnimSet);
	}

	SetupBoneMatrixPtrs(m_pRootFrame);
}

void cSkinnedMesh::Update()
{
	m_vecAnimationSet[m_nCurrentAnimation]->Update();

	if(m_isAnimationBlending)
	{
		m_fPassedBlendTime += g_pTimeManager->GetDeltaTime();
		if(m_fPassedBlendTime >= m_fAnimationBlendTime)
		{
			m_isAnimationBlending = false;
			m_pAnimControl->SetTrackWeight(0, 1.0f);
			m_pAnimControl->SetTrackWeight(1, 0.0f);
			m_pAnimControl->SetTrackEnable(1, false);
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fAnimationBlendTime;
			m_pAnimControl->SetTrackWeight(0, fWeight);
			m_pAnimControl->SetTrackWeight(1, 1.0f - fWeight);
		}
	}
	m_pAnimControl->AdvanceTime(g_pTimeManager->GetDeltaTime(), NULL);

	UpdateWorldMatrix(m_pRootFrame, NULL);

	UpdateSkinnedMesh(m_pRootFrame);
}

void cSkinnedMesh::Render()
{
	Render(m_pRootFrame);
}


void cSkinnedMesh::UpdateWorldMatrix( D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParent )
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->matWorldTM = pBone->TransformationMatrix;
	
	if(pmatParent)
	{
		pBone->matWorldTM = pBone->matWorldTM * (*pmatParent);
	}

	if(pBone->pFrameSibling)
	{
		UpdateWorldMatrix(pBone->pFrameSibling, pmatParent);
	}
	if(pBone->pFrameFirstChild)
	{
		UpdateWorldMatrix(pBone->pFrameFirstChild, &pBone->matWorldTM);
	}
}

void cSkinnedMesh::Render( D3DXFRAME* pFrame )
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->matWorldTM);

	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		for (size_t i = 0; i < pBoneMesh->dwNumSubset; ++i)
		{
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->pTex);
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->stMtl);
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
		}
	}
	if(pBone->pFrameSibling)
	{
		Render(pBone->pFrameSibling);
	}
	
	if(pBone->pFrameFirstChild)
	{
		Render(pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::SetAnimationIndex( DWORD dwIndex )
{
	if(dwIndex >= m_vecAnimationSet.size())
		return;

	cAnimationSet* pCurr = m_vecAnimationSet[m_nCurrentAnimation];
	cAnimationSet* pNext = m_vecAnimationSet[dwIndex];
	if(pNext->GetIsLoop())
	{
		SetAnimationIndexBlend(dwIndex);
	}
	else
	{
		pNext->SetDelegate(this);
		pNext->SetPrevAnimation(pCurr);
		pNext->Start();
		SetAnimationIndexBlend(dwIndex);
	}
	m_nCurrentAnimation = dwIndex;
}

void cSkinnedMesh::SetAnimationIndexBlend( DWORD dwIndex )
{
	LPD3DXANIMATIONSET pPrev = NULL;
	LPD3DXANIMATIONSET pNext = NULL;

	m_pAnimControl->GetAnimationSet(dwIndex, &pNext);
	if(!pNext)
	{
		return;
	}
	m_pAnimControl->GetTrackAnimationSet(0, &pPrev);

	D3DXTRACK_DESC desc;
	m_pAnimControl->GetTrackDesc(0, &desc);
	m_pAnimControl->SetTrackDesc(1, &desc);

	m_pAnimControl->SetTrackWeight(0, 0.0f);
	m_pAnimControl->SetTrackWeight(1, 1.0f);

	m_pAnimControl->SetTrackAnimationSet(0, pNext);
	m_pAnimControl->SetTrackAnimationSet(1, pPrev);

	SAFE_RELEASE(pPrev);
	SAFE_RELEASE(pNext);

	m_fPassedBlendTime = 0.0f;
	m_isAnimationBlending = true;
}

void cSkinnedMesh::SetAnimationLoop( DWORD dwIndex, bool isLoop )
{
	if(dwIndex < m_vecAnimationSet.size())
	{
		m_vecAnimationSet[dwIndex]->SetIsLoop(isLoop);
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs( D3DXFRAME* pFrame )
{
	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.

	if(pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
			// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
			// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
			// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
			// ã�Ƽ� �����Ʈ������ �ɾ����.
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRootFrame, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &pBone->matWorldTM;
			}
		}
	}
	
	ST_BONE* pBone = (ST_BONE*)pFrame;
	//��������� ��� �����ӿ� ���ؼ� ����.
	if(pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pBone->pFrameSibling);
	}

	if(pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::UpdateSkinnedMesh( D3DXFRAME* pFrame )
{

	if(pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				// pCurrentBoneMatrices �� ����Ͻÿ�
				// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 

				pBoneMesh->pCurrentBoneMatrices[i] = 
					pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}

			BYTE* src = NULL;
			BYTE* dest = NULL;

			pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
			pBoneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );

			//MeshData.pMesh�� ������Ʈ �����ش�.
			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		}
	}

	ST_BONE* pBone = (ST_BONE*)pFrame;
	//��������� ��� �����ӿ� ���ؼ� ����.
	if(pBone->pFrameSibling)
	{
		UpdateSkinnedMesh(pBone->pFrameSibling);
	}

	if(pBone->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::OnFinishAnimation( cAnimationSet* pSender )
{
	SetAnimationIndex(pSender->GetPrevAnimation()->GetIndex());
}