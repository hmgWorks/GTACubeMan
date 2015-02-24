#pragma once
/*
	in game
	���� ������ ���� �Ǵ� ��

*/
__interface iButtonDelegate;

class cGrid;
class cCamera;
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
		
	std::vector<cGroup*> m_vecGroup;

public:
	cScenePlayGame();
	virtual ~cScenePlayGame();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

