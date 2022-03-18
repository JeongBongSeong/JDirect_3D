#include "JObject3D.h"


void JObject3D::AddPosition(JVector3 vPos)
{
	m_vPos = m_vPos + vPos;
	// 오브젝트의 위치값설정 
	m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);

	SetVertexData();
	SetIndexData();
	if (m_pContext != nullptr)
	{
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	}

}
void JObject3D::SetPosition(JVector3 vPos)
{
	m_vPos = vPos;
	SetRectDraw({
		(LONG)(m_vPos.x - m_rtDraw.right / 2.0f),
		(LONG)(m_vPos.y - m_rtDraw.bottom / 2.0f),
		m_rtDraw.right,
		m_rtDraw.bottom });
	m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
	SetVertexData();
	SetIndexData();
	if (m_pContext != nullptr)
	{
		m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	}
}
bool    JObject3D::SetVertexData()
{
	return true;
}
bool    JObject3D::SetIndexData()
{
	m_IndexList.clear();
	//// 0   1,4
	//// 2,3  5
	//DWORD indeces[] = {
	//	0,1,2,
	//	3,4,5,
	//};
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	return true;
}

void    JObject3D::FadeIn()
{
	m_fAlpha += g_fSecPerFrame * 0.5f;
	m_fAlpha = min(m_fAlpha, 1.0f);
	if (m_fAlpha >= 1.0f)
	{
		m_bFadeIn = false;
	}
}
void    JObject3D::FadeOut()
{
	m_fAlpha = m_fAlpha - g_fSecPerFrame * 0.5f;
	m_fAlpha = max(m_fAlpha, 0.0f);
	if (m_fAlpha <= 0.0f)
	{
		m_bFadeOut = false;
	}
}
bool	JObject3D::Frame()
{
	if (m_bFadeIn)	FadeIn();
	if (m_bFadeOut)	FadeOut();
	m_ConstantList.Color = m_vColor;
	m_ConstantList.Timer = JVector4(
		g_fGameTimer,
		0,
		0,
		1.0f);
	m_pContext->UpdateSubresource(
		m_pConstantBuffer, 0, NULL, &m_ConstantList, 0, 0);
	return true;
}

JObject3D::JObject3D()
{
	m_fAlpha = 1.0f;
	m_vColor = JVector4(1, 1, 1, 1);
	m_rtSource.left = 0; m_rtSource.right = 0;
	m_rtSource.top = 0; m_rtSource.bottom = 0;
	m_rtDraw.left = 0; m_rtDraw.right = g_rtClient.right;
	m_rtDraw.top = 0; m_rtDraw.bottom = g_rtClient.bottom;
}
JObject3D::~JObject3D()
{

}