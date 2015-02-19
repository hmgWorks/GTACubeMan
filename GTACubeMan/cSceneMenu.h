#pragma once
class cSceneMenu
	:public iSceneBase
{
private:
	LPD3DXSPRITE	m_pSprite;
	cUIObject*		m_pUIRoot;

public:
	cSceneMenu();
	virtual ~cSceneMenu();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

