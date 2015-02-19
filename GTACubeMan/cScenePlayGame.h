#pragma once
/*
	in game
	���� ������ ���� �Ǵ� ��

*/
__interface iButtonDelegate;

class cGrid;
class cCamera;

class cScenePlayGame
	:public iSceneBase
{
private:
	cGrid*		m_pGrid;
	cCamera*	m_pCamera;
	

public:
	cScenePlayGame();
	virtual ~cScenePlayGame();

	void Setup(iButtonDelegate* dele, cCamera* camera = NULL) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

