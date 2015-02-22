#pragma once
class cCamera;
class cSkinnedMesh;


__interface iButtonDelegate
{
public:
	void OnClick(cObject* pSender);
	cCamera* GetCamera();
	void Menu();
	cSkinnedMesh* GetSkinnedMesh();
	//void InitPlayer();
}; 