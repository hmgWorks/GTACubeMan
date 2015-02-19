#pragma once
class cSceneNewPlay
	:public iSceneBase
{
public:
	cSceneNewPlay();
	virtual ~cSceneNewPlay();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

