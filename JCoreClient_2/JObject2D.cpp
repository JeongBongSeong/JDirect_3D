#include "JObject2D.h"
void JObject2D::SetRectSource(RECT rt)
{
	m_rtSource = rt;
}
void JObject2D::SetRectDraw(RECT rt)
{
	m_rtDraw = rt;
	m_fWidth = rt.right;
	m_fHeight = rt.bottom;
}
void JObject2D::AddPosition(JVector2 vPos)
{
	m_vPos = m_vPos + vPos;
	Convert(m_vPos, m_fWidth, m_fHeight, m_VertexList);
	m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0); 
	
}
void JObject2D::SetPosition(JVector2 vPos)
{
	m_vPos = vPos;
}
void JObject2D::UpdateRectDraw(RECT rt)
{
	m_fWidth = rt.right;
	m_fHeight = rt.bottom;
}
void JObject2D::Convert(JVector2 center, float fWidth, float fHeight, vector<SimpleVertex>& retList)
{
	// --      +-
	// -+      ++
	vector<SimpleVertex> list(6);
	float halfWidth = fWidth / 2.0f;
	float halfHeight = fHeight / 2.0f;
	list[0].v = { center.x - halfWidth, center.y - halfHeight };
	list[1].v = { center.x + halfWidth, center.y - halfHeight };
	list[2].v = { center.x - halfWidth, center.y + halfHeight };
	list[3].v = list[2].v;
	list[4].v = list[1].v;
	list[5].v = { center.x + halfWidth, center.y + halfHeight };

	Convert(list, retList);
}
void JObject2D::Convert(vector<SimpleVertex>& list, vector<SimpleVertex>& retList)
{
	retList.resize(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		// 0 ~ 800 -> 0 ~ 1 -> -1 ~ +1
		retList[i].v.x = list[i].v.x / g_rtClient.right;
		retList[i].v.y = list[i].v.y / g_rtClient.bottom;
		// 0 ~ 1 -> -1 ~ +1 :::: -1 ~ +1 -> 0 ~ 1
		// x = x * 2 + -1;  ::::  x= x * 0.5f + 0.5f;
		retList[i].v.x = retList[i].v.x * 2.0f - 1.0f;
		retList[i].v.y = -1.0f * (retList[i].v.y * 2.0f - 1.0f);
	}
	float u = m_rtSource.left / (float)m_TextureDesc.Width;
	float v = m_rtSource.top / (float)m_TextureDesc.Height;
	float w = m_rtSource.right / (float)m_TextureDesc.Width;
	float h = m_rtSource.bottom / (float)m_TextureDesc.Height;
	retList[0].t.x = u; retList[0].t.y = v;
	retList[1].t.x = u+w; retList[1].t.y = v;
	retList[2].t.x = u; retList[2].t.y = v+h;
	retList[3].t = retList[2].t;
	retList[4].t = retList[1].t;
	retList[5].t.x = u+w; retList[5].t.y = v+h;
}
bool JObject2D::SetVertexData()
{
	Convert(m_vPos, m_fWidth, m_fHeight, m_VertexList);
    return true;
}
