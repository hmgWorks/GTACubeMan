#pragma once
__interface iButtonDelegate;

class cSceneInGame :
	public iSceneBase
{
private:

public:
	cSceneInGame();
	virtual ~cSceneInGame();

	void Setup(iButtonDelegate* dele) override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

