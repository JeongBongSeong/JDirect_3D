#pragma once
#include "JObject2D.h"
#include "JObjectMgr.h"
#include "JEffectObj.h"
class JObjectNpc2D : public JObject2D
{
public:
	JSprite* m_pSprite = nullptr;
	JEffectObj m_NpcAttackExplosionObj;
	int m_iCurrentIndex = 0;
	float m_fChangeTime = 0.0f;
	float m_fTimer = 0.0f;
	float m_fAttackTime = 0.0f;
	float m_fWaitTime = 1.0f;
	RECT m_rtIngame = {0,0,0,0};
public:
	bool Frame() override;
	bool Render() override;
public:
	void Anime(JVector2 pos);
	void HitOverlap(JBaseObject* pObj, DWORD dwState);
	void HitSelect(JBaseObject* pObj, DWORD dwState);
	void  UpdateData() override
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&JBaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}
public:
	JObjectNpc2D();
	virtual ~JObjectNpc2D();
};