#pragma once
class cSceneSelectPlayData
	:public iSceneBase
{
public:
	cSceneSelectPlayData();
	virtual ~cSceneSelectPlayData();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

