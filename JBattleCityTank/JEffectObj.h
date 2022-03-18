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
	JVector2 m_vTargetPosition;
public:
	virtual void HitSelect(JBaseObject* pObj, DWORD dwState) override;
	virtual void Reset();
public:			 
	virtual void SetTargetPosition(JVector2* pos)
	{
		m_vTargetPosition = *pos;
	}
	virtual bool Init() override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
};

