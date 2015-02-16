#pragma once

class cUIObject : public cObject
{
protected:
	D3DXMATRIXA16			m_matWorld;
	std::vector<cUIObject*> m_vecChild;
	cUIObject*				m_pParent;
	LPD3DXSPRITE			m_pSprite;

	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);
	SYNTHESIZE_PASS_BY_REF(ST_SIZE,	m_stSize, Size);

public:
	cUIObject(LPD3DXSPRITE pSprite);
	virtual ~cUIObject(void);

	virtual void AddChild(cUIObject* pChild);

	virtual void Update();

	virtual void Render();

	virtual void Destroy();

	virtual void SetPosition(float x, float y)
	{
		m_vPosition.x = x;
		m_vPosition.y = y;
	}
};

