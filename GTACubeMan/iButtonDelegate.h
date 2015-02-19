#pragma once
class cCamera;

__interface iButtonDelegate
{
public:
	void OnClick(cObject* pSender);
	cCamera* GetCamera();
}; 