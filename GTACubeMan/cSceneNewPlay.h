#pragma once
/*
	
*/
__interface iButtonDelegate;


class cSceneNewPlay
	:public iSceneBase
{
private:
	LPD3DXSPRITE	m_pSprite;
	cUIObject*		m_pUIRoot;
	

public:
	cSceneNewPlay();
	virtual ~cSceneNewPlay();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

