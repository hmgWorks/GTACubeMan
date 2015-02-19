#pragma once
class cSceneMenu
	:public iSceneBase
{
public:
	cSceneMenu();
	virtual ~cSceneMenu();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

