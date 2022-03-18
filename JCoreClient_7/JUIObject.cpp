#include "JUIObject.h"

bool JUIObject::Frame()
{
	JDxObject::Frame();
	return true;
}

bool JUIObject::Render()
{
	JDxObject::Render();
	return true;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool JImageObject::Init()
{
	m_bFadeIn = true;
	return true;
}

bool JImageObject::Frame()
{
	JDxObject::Frame();
	if (m_bFadeIn) FadeIn();
	if (m_bFadeOut) FadeOut();
	m_ConstantList.Color = JVector4(m_fAlpha, m_fAlpha, m_fAlpha, 1.0f);
	m_ConstantList.Timer = JVector4(g_fGameTimer, 0, 0, 1.0f);
	
	//상수 버퍼 
	m_pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);


	return true;
}

bool JImageObject::Render()
{
	JDxObject::Render();
	return true;
}

void JImageObject::FadeIn()
{
	m_fAlpha += g_fSecPerFrame * 0.5f;
	m_fAlpha = min(m_fAlpha, 1.0f);
	if (m_fAlpha >= 1.0f)
	{
		m_bFadeIn = false;
	}
}

void JImageObject::FadeOut()
{
	m_fAlpha -= g_fSecPerFrame * 0.5f;
	m_fAlpha = max(m_fAlpha, 0.0f);
	if (m_fAlpha <= 0.0f)
	{
		m_bFadeOut = false;
	}
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool JButtonObject::Frame()
{
	JDxObject::Frame();
	return true;
}

bool JButtonObject::Render()
{
	JDxObject::Render();
	return true;
}
