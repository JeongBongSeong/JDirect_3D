#pragma once
#include "JObject2D.h"
#include "JObjectMgr.h"

class JTileObj2D : public JObject2D
{
public:
	//JSprite* m_pSprite = nullptr;
	JVector2 m_vStart;
public:
	bool Frame() override;
public:
	void SettingPosition(JVector2* pos, JVector2* dir);
	void HitOverlap(JBaseObject* pObj, DWORD dwState);
	void SetEffect();

	void  UpdateData() override
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		I_ObjectMgr.AddPlayerCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}

public:
	JTileObj2D();
	virtual ~JTileObj2D();
};

