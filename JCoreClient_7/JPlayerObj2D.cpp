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
	//ȭ��ȿ� �ӹ����ϱ�

    if (JInput::Get().GetKey(VK_UP) == KEY_HOLD)
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
	if (JInput::Get().GetKey(VK_LEFT) == KEY_HOLD)
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
	if (JInput::Get().GetKey(VK_DOWN) == KEY_HOLD)
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
	if (JInput::Get().GetKey(VK_RIGHT) == KEY_HOLD)
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
