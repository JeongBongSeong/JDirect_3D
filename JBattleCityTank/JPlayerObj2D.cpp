#include "JPlayerObj2D.h"
#include "JInput.h"

void JPlayerObj2D::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
	if (dwState == JCollisionType::Overlap)
	{
		int a = 0;
	//	pObj->m_bAlphaBlend = !pObj->m_bAlphaBlend;
	}
}

bool JPlayerObj2D::Frame()
{
	//화면안에 머물게하기
	
    if (JInput::Get().GetKey(VK_UP) == KEY_HOLD)
	{
		JVector2 pos;
		//UpdateRectSource();
		if (m_vPos.y < g_rtClient.top + 40.0f)
		{
			pos.y = 0;
		}
		else 
		{
			pos.y -= m_fSpeed * g_fSecPerFrame;
		}
	}
	else if (JInput::Get().GetKey(VK_LEFT) == KEY_HOLD)
	{
		JVector2 pos;
		if (m_vPos.x < g_rtClient.left + 40.0f)
		{
			pos.x = 0;
		}
		else
		{
			pos.x -= m_fSpeed * g_fSecPerFrame;
		}
	}
	else if (JInput::Get().GetKey(VK_DOWN) == KEY_HOLD)
	{
		JVector2 pos;
		if (m_vPos.y > g_rtClient.bottom - 40.0f)
		{
			pos.y = 0;
		}
		else
		{
			pos.y += m_fSpeed * g_fSecPerFrame;
		}
	}
	else if (JInput::Get().GetKey(VK_RIGHT) == KEY_HOLD)
	{
		JVector2 pos;
		if (m_vPos.x > g_rtClient.right - 40.0f)
		{
			pos.x = 0;
		}
		else
		{
			pos.x += m_fSpeed * g_fSecPerFrame;
		}
	}
	
	JObject2D::Frame();
	return true;

}


void JPlayerObj2D::UpdateRectSource(RECT rt)
{
	
}

void JPlayerTank::Anime(JVector2 pos)
{
	m_fChangeTime = m_pSprite->m_fAnimTime / m_pSprite->m_rtArray.size();
	m_fTimer += g_fSecPerFrame;
	if (m_fTimer >= m_fChangeTime)
	{
		m_iCurrentIndex++;
		if (m_iCurrentIndex >= m_pSprite->m_rtArray.size())
		{
			m_iCurrentIndex = 0;
			//m_bDead = true;
		}
		m_fTimer -= m_fChangeTime;
		SetRectSource(m_pSprite->m_rtArray[m_iCurrentIndex]);

	}
	AddPosition(pos);
}

bool JPlayerTank::isCannonBall()
{
	for (auto obj : m_CannonBallObj)
	{
		JObject2D* pObj = obj.get();
		if (pObj->m_bDead == true)
		{
			return true;
		}

	}
	return false;
}

JPlayerObj2D::JPlayerObj2D()
{
	m_fSpeed = 150.0f;
	m_dwCollisionType = JCollisionType::Overlap;
	m_dwSelectType = JSelectType::Select_Overlap;
}

JPlayerObj2D::~JPlayerObj2D()
{
}

bool JPlayerTank::Frame()
{
	//화면안에 머물게하기
	
	if (JInput::Get().GetKey(VK_UP) == KEY_HOLD)
	{
		JVector2 pos;
		//UpdateRectSource();
		if (m_vPos.y < m_rtIngame.top + 30.0f)
		{
			pos.y = 0;
		}
		else
		{
			pos.y -= m_fSpeed * g_fSecPerFrame;
		}
		Anime(pos);
		m_vDirection = JVector2(0, -1);
		m_vMuzzlePosition = JVector2(m_vPos.x, m_vPos.y - (m_fHeight / 2));
	}
	else if (JInput::Get().GetKey(VK_LEFT) == KEY_HOLD)
	{
		JVector2 pos;
		if (m_vPos.x < m_rtIngame.left + 30.0f)
		{
			pos.x = 0;
		}
		else
		{
			pos.x -= m_fSpeed * g_fSecPerFrame;
		}
		Anime(pos);
		m_vDirection = JVector2(-1, 0);
		m_vMuzzlePosition = JVector2(m_vPos.x - (m_fWidth / 2), m_vPos.y);
	}
	else if (JInput::Get().GetKey(VK_DOWN) == KEY_HOLD)
	{
		JVector2 pos;
		if (m_vPos.y > m_rtIngame.bottom - 30.0f)
		{
			pos.y = 0;
		}
		else
		{
			pos.y += m_fSpeed * g_fSecPerFrame;
		}
		Anime(pos);
		m_vDirection = JVector2(0, 1);
		m_vMuzzlePosition = JVector2(m_vPos.x, m_vPos.y + (m_fHeight / 2));
	}
	else if (JInput::Get().GetKey(VK_RIGHT) == KEY_HOLD)
	{
		JVector2 pos;
		if (m_vPos.x > m_rtIngame.right - 30.0f)
		{
			pos.x = 0;
		}
		else
		{
			pos.x += m_fSpeed * g_fSecPerFrame;
		}
		Anime(pos);
		m_vDirection = JVector2(1, 0);
		m_vMuzzlePosition = JVector2(m_vPos.x + (m_fWidth / 2), m_vPos.y);
	}
	if (isCannonBall())
	{
		for (int i = 0; i < m_CannonBallObj.size(); i++)
		{
			if (m_CannonBallObj[i]->m_bDead == true)
			{
				m_CannonBallObj[i]->SettingPosition(&m_vMuzzlePosition, &m_vDirection);
			}
		}
	}
	for (auto obj : m_CannonBallObj)
	{
		JObject2D* pObj = obj.get();
		if (pObj->m_bDead == false)
		{
			pObj->Frame();
		}
	}

	JObject2D::Frame();
	return false;
}

bool JPlayerTank::Render()
{	
	for (auto obj : m_CannonBallObj)
	{
		JObject2D* pObj = obj.get();
		if (pObj->m_bDead == false)
		{
			pObj->Render();
		}
	}
	JObject2D::Render();
	return false;
}
