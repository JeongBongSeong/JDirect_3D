#include "JEffectObj.h"
void JEffectObj::HitSelect(JBaseObject* pObj, DWORD dwState)
{
	int k = 0;
}
void JEffectObj::Reset()
{
	m_bDead = false;
	m_fTimer = 0.0f;
	m_iCurrentIndex = 0;
}
bool JEffectObj::Init()
{
	m_vColor = JVector4(1, 1, 1, 1.0f);
	return true;
}
bool JEffectObj::Frame()
{
	if (m_bDead) return true;
	m_fChangeTime = m_pSprite->m_fAnimTime / m_pSprite->m_rtArray.size();
	m_fTimer += g_fSecPerFrame;

	if (m_fTimer >= m_fChangeTime)
	{
		m_iCurrentIndex++;
		if (m_iCurrentIndex >= m_pSprite->m_rtArray.size())
		{
			m_iCurrentIndex = 0;
			m_bDead = true;
		}
		m_fTimer -= m_fChangeTime;
		SetRectSource(m_pSprite->m_rtArray[m_iCurrentIndex]);
		SetRectDraw({ 0,0,
			m_pSprite->m_rtArray[m_iCurrentIndex].right,
			m_pSprite->m_rtArray[m_iCurrentIndex].bottom });
	}
	AddPosition({ 0,0 });
	return true;
}
bool JEffectObj::Render()
{
	if (m_bDead) return true;
	JDxObject::Render();
	return true;
}
bool JEffectObj::Release()
{
	JObject2D::Release();
	return true;
}