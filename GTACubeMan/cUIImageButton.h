#pragma once

class cUIImageButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cUIImageButton* pSender) = 0;
};

class cUIImageButton : public cUIObject
{
protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSE_OVER,
		E_SELECTED
	};

	eButtonState m_eButtonState;

	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE_PASS_BY_REF(std::string, m_sNormal, Normal);
	SYNTHESIZE_PASS_BY_REF(std::string, m_sMouseOver, MouseOver);
	SYNTHESIZE_PASS_BY_REF(std::string, m_sSelected, Selected);

public:
	cUIImageButton(LPD3DXSPRITE pSprite);
	~cUIImageButton(void);

	virtual void Setup(
		std::string sNormal, 
		std::string sMouseOver,
		std::string sSelected);

	virtual void Update() override;

	virtual void Render() override;
};

