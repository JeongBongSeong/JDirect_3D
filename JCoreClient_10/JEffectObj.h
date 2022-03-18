#pragma once
#include "JObject2D.h"
#include "JSprite.h"

class JEffectObj : public JObject2D
{
public:
	JSprite* m_pSprite;
	int m_iCurrentIndex = 0;
	float m_fChangeTime;
	float m_fTimer = 0.0f;
public:
	virtual void HitSelect(JBaseObject* pObj, DWORD dwState) override;
	virtual void Reset();
public:			 
	virtual bool Init() override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
};

