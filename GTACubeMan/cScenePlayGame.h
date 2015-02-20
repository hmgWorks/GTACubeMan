#pragma once
/*
	in game
	���� ������ ���� �Ǵ� ��

*/
__interface iButtonDelegate;

class cGrid;
class cCamera;
class cFrame;

class cScenePlayGame
	:public iSceneBase
{
private:
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;
	iButtonDelegate* m_pButtonDelegate;
	cFrame*			m_pAseRoot;

public:
	cScenePlayGame();
	virtual ~cScenePlayGame();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

