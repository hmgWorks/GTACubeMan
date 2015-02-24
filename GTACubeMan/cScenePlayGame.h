#pragma once
/*
	in game
	실재 게임이 진행 되는 곳

*/
__interface iButtonDelegate;

class cGrid;
class cCamera;
//class cFrame;
class cSkinnedMesh;
class cGroup;

class cScenePlayGame
	:public iSceneBase
{
private:
	cGrid*				m_pGrid;
	cCamera*			m_pCamera;
	iButtonDelegate*	m_pButtonDelegate;
	cSkinnedMesh*		m_pSkinnedMesh;
	//cFrame*				m_pAseRoot;
	//std::vector<cFrame*> m_vecAseBackgriund;
	
	std::vector<cGroup*> m_vecGroup;

public:
	cScenePlayGame();
	virtual ~cScenePlayGame();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

