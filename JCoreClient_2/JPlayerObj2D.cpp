#include "JPlayerObj2D.h"
#include "JInput.h"

bool JPlayerObj2D::Frame()
{
    if (JInput::Get().GetKey('W') == KEY_HOLD)
	{
		JVector2 pos;
		pos.y -= m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (JInput::Get().GetKey('A') == KEY_HOLD)
	{
		JVector2 pos;
		pos.x -= m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (JInput::Get().GetKey('S') == KEY_HOLD)
	{
		JVector2 pos;
		pos.y += m_fSpeed * g_fSecPerFrame;
		AddPosition(pos);
	}
	if (JInput::Get().GetKey('D') == KEY_HOLD)
	{
		JVector2 pos;
		pos.x += m_fSpeed * g_fSecPerFrame;
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
