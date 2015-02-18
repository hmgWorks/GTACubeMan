#pragma once
class cSceneEnd
	:public iSceneBase
{
public:
	cSceneEnd();
	virtual ~cSceneEnd();

	void Setup(iButtonDelegate* dele, cCamera* camera = NULL) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

