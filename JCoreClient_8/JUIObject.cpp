#include "JUIObject.h"

bool JUIObject::Frame()
{
	JObject2D::Frame();
	return true;
}

bool JUIObject::Render()
{
	JObject2D::Render();
	return true;
}

bool JImageObject::Init()
{
	return true;
}

bool JImageObject::Frame()
{
	m_vColor.x = m_fAlpha;
	m_vColor.y = m_fAlpha;
	m_vColor.z = m_fAlpha;
	m_vColor.w = 1.0f;
	JObject2D::Frame();
	return true;
}

bool JImageObject::Render()
{
	JObject2D::Render();
	return true;
}

bool JButtonObject::Init()
{
	return true;
}


bool JButtonObject::Frame()
{
	if (m_dwSelectState & J_FOCUS)
	{
		m_vColor.x = 0;
		m_vColor.y = 1;
		m_vColor.z = 1;
		m_vColor.w = 1.0f;
	}
	else 
	{
		m_vColor.x = 1;
		m_vColor.y = 1;
		m_vColor.z = 1;
		m_vColor.w = 1.0f;
	}
	JObject2D::Frame();
	
	return true;
}

bool JButtonObject::Render()
{
	JObject2D::Render();
	return true;
}

void JButtonObject::HitSelect(JBaseObject* pObj, DWORD dwState)
{
	if (m_dwSelectState == JSelectState::J_SELECTED)
	{
		JWorld::m_pWorld->m_bLoadZone = true;
	}
}