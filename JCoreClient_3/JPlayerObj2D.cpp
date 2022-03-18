#include "JPlayerObj2D.h"
#include "JInput.h"

void JPlayerObj2D::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
	if (dwState == JCollisionType::Overlap)
	{
		pObj->m_bAlphaBlend = FALSE;
	}
}

bool JPlayerObj2D::Frame()
{
	//화면안에 머물게하기

    if (JInput::Get().GetKey('W') == KEY_HOLD)
	{
		JVector2 pos;
		if (m_vPos.y < g_rtClient.top + 40.0f)
		{
			pos.y = 0;
		}
		else 
		{
			pos.y -= m_fSpeed * g_fSecPerFrame;
		}
		
		AddPosition(pos);
	}
	if (JInput::Get().GetKey('A') == KEY_HOLD)
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
		AddPosition(pos);
	}
	if (JInput::Get().GetKey('S') == KEY_HOLD)
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
		AddPosition(pos);
	}
	if (JInput::Get().GetKey('D') == KEY_HOLD)
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
		AddPosition(pos);
	}
	return true;

}

JPlayerObj2D::JPlayerObj2D()
{
	m_fSpeed = 600.0f;
}

JPlayerObj2D::~JPlayerObj2D()
{
}
