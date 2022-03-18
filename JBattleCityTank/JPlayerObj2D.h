#pragma once
#include "JObject2D.h"
#include "JObjectMgr.h"
#include "JSprite.h"
#include "JAttackObj2D.h"
//struct JStatePlayerData
//{
//	JTexture* pTex;
//	JSound* pSound;
//	JStatePlayerData(const JStatePlayerData& data)
//	{
//		pTex = data.pTex;
//		pSound = data.pSound;
//		DisplayText("JStatePlayDataCopy\n");
//	}
//	JStatePlayerData()
//	{
//		DisplayText("JStatePlayData\n");
//	}
//	JStatePlayerData(JTexture* a, JSound* b)
//	{
//		pTex = a;
//		pSound = b;
//		DisplayText("JStatePlayData\n");
//	}
//};
class JPlayerObj2D : public JObject2D
{
public:
	virtual void HitOverlap(JBaseObject* pObj, DWORD dwState);
	bool	Frame() override;
	//bool	Render() override;
	void  UpdateData() override
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		I_ObjectMgr.AddPlayerCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		/*I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&JBaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));*/
	}
public:
	void UpdateRectSource(RECT rt) override;
public:
	JPlayerObj2D();
	virtual ~JPlayerObj2D();
};

class JPlayerTank : public JPlayerObj2D
{
public:
	//	vector<RECT*> m_list;
		//std::shared_ptr<JSprite> m_pSprite;
	JSprite* m_pSprite = nullptr;
	int m_iCurrentIndex = 0;
	float m_fChangeTime = 0.0f;
	float m_fTimer = 0.0f;
	float m_fAttackTime = 0.0f;
	float m_fWaitTime = 0.0f;		//ÄðÅ¸ÀÓ
	float m_fWaitTime = 1.0f;
	RECT m_rtIngame;
public:
	JVector2 m_vDirection;
	JVector2 m_vMuzzlePosition;
	std::vector<std::shared_ptr<JAttackObj2D>> m_CannonBallObj;
	
	//std::vector<JStatePlayerData> m_pStatePlayList;
public:
	bool	Frame() override;
	bool Render() override; 
	void Anime(JVector2 pos);
public:
	bool isCannonBall();
public:
	JPlayerTank() { };
	virtual ~JPlayerTank() { if (m_pSprite) m_pSprite->Release(); m_pSprite = nullptr; };
};