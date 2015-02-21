#pragma once
class cCamera;
class cSkinnedMesh;


__interface iButtonDelegate
{
public:
	void OnClick(cObject* pSender);
	cCamera* GetCamera();
	void MenuSetting();
	cSkinnedMesh* GetSkinnedMesh();
	void InitPlayer();
}; 