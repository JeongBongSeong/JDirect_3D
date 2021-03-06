#include "JUIObject.h"

bool JUIObject::SetVertexData()
{
	//ConvertIndex(m_vPos, m_fWidth, m_fHeight, m_VertexList);
	// 0  a   1     2  b   3
	// c  lt          rt
	// 4     5      6     7
	//              
	// 8     9     10    11
	// d lb           rb 
	// 12    13    14    15 
	JVector2 vLT = { (float)m_rtOffset.left,  (float)m_rtOffset.top };
	JVector2 vRT = { (float)m_rtOffset.right, (float)m_rtOffset.top };
	JVector2 vLB = { (float)m_rtOffset.left, (float)m_rtOffset.bottom };
	JVector2 vRB = { (float)m_rtOffset.right, (float)m_rtOffset.bottom };

	float fWidth = m_fWidth;
	float fHeight = m_fHeight;
	if (m_pColorTex != nullptr)
	{
		fWidth = m_pColorTex->m_TextureDesc.Width;
		fHeight = m_pColorTex->m_TextureDesc.Height;
	}

	JVector2 tLT = { vLT.x / fWidth, vLT.y / fHeight };
	JVector2 tRT = { vRT.x / fWidth, vRT.y / fHeight };
	JVector2 tLB = { vLB.x / fWidth, vLB.y / fHeight };
	JVector2 tRB = { vRT.x / fWidth, vRT.y / fHeight };



	std::vector<SimpleVertex> list(16);
	float halfWidth = m_fWidth / 2.0f;
	float halfHeight = m_fHeight / 2.0f;
	list[0].v = { m_vPos.x - halfWidth, m_vPos.y - halfHeight };
	list[0].t = { (float)m_rtOffsetTex.left,(float)m_rtOffsetTex.top };
	list[3].v = { m_vPos.x + halfWidth, m_vPos.y - halfHeight };
	list[3].t = { (float)m_rtOffsetTex.right,(float)m_rtOffsetTex.top };
	list[12].v = { m_vPos.x - halfWidth, m_vPos.y + halfHeight };
	list[12].t = { (float)m_rtOffsetTex.left,(float)m_rtOffsetTex.bottom };
	list[15].v = { m_vPos.x + halfWidth, m_vPos.y + halfHeight };
	list[15].t = { (float)m_rtOffsetTex.right,(float)m_rtOffsetTex.bottom };
	list[5].v = { list[0].v.x + vLT.x, list[0].v.y + vLT.y };
	list[5].t = { list[0].t.x + tLT.x, list[0].t.y + tLT.y };
	list[6].v = { list[3].v.x - vRT.x, list[3].v.y + vRT.y };
	list[6].t = { list[3].t.x - tRT.x, list[3].t.y + tRT.y };
	list[9].v = { list[12].v.x + vLB.x, list[12].v.y - vLB.y };
	list[9].t = { list[12].t.x + tLB.x, list[12].t.y - tLB.y };
	list[10].v = { list[15].v.x - vRB.x, list[15].v.y - vRB.y };
	list[10].t = { list[15].t.x - tRB.x, list[15].t.y - tRB.y };

	list[1].v = { list[5].v.x, list[0].v.y };
	list[1].t = { list[5].t.x, list[0].t.y };
	list[2].v = { list[6].v.x, list[3].v.y };
	list[2].t = { list[6].t.x, list[3].t.y };

	list[4].v = { list[0].v.x, list[5].v.y };
	list[4].t = { list[0].t.x, list[5].t.y };
	list[7].v = { list[3].v.x, list[6].v.y };
	list[7].t = { list[3].t.x, list[6].t.y };

	list[8].v = { list[12].v.x, list[9].v.y };
	list[8].t = { list[12].t.x, list[9].t.y };
	list[11].v = { list[15].v.x, list[10].v.y };
	list[11].t = { list[15].t.x, list[10].t.y };

	list[13].v = { list[9].v.x, list[12].v.y };
	list[13].t = { list[9].t.x, list[12].t.y };
	list[14].v = { list[10].v.x, list[15].v.y };
	list[14].t = { list[10].t.x, list[15].t.y };

	for (int i = 0; i < list.size(); i++)
	{
		// 0 ~ 800 -> 0 ~ 1 -> -1 ~ +1
		list[i].v.x = list[i].v.x / g_rtClient.right;
		list[i].v.y = list[i].v.y / g_rtClient.bottom;
		// 0 ~ 1 -> -1 ~ +1 :::: -1 ~ +1 -> 0 ~ 1
		// x = x * 2 + -1;  ::::  x= x * 0.5f + 0.5f;
		list[i].v.x = list[i].v.x * 2.0f - 1.0f;
		list[i].v.y = -1.0f * (list[i].v.y * 2.0f - 1.0f);
	}
	m_VertexList = list;
	return true;
}
bool JUIObject::SetIndexData()
{
	// 0  a   1     2  b   3
	// c  lt          rt
	// 4     5      6     7
	//              
	// 8     9     10    11
	// d lb           rb 
	// 12    13    14    15 
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(4);
	m_IndexList.push_back(4); m_IndexList.push_back(1); m_IndexList.push_back(5);
	m_IndexList.push_back(1); m_IndexList.push_back(2); m_IndexList.push_back(5);
	m_IndexList.push_back(5); m_IndexList.push_back(2); m_IndexList.push_back(6);
	m_IndexList.push_back(2); m_IndexList.push_back(3); m_IndexList.push_back(6);
	m_IndexList.push_back(6); m_IndexList.push_back(3); m_IndexList.push_back(7);

	m_IndexList.push_back(4); m_IndexList.push_back(5); m_IndexList.push_back(8);
	m_IndexList.push_back(8); m_IndexList.push_back(5); m_IndexList.push_back(9);
	m_IndexList.push_back(5); m_IndexList.push_back(6); m_IndexList.push_back(9);
	m_IndexList.push_back(9); m_IndexList.push_back(6); m_IndexList.push_back(10);
	m_IndexList.push_back(6); m_IndexList.push_back(7); m_IndexList.push_back(10);
	m_IndexList.push_back(10); m_IndexList.push_back(7); m_IndexList.push_back(11);


	m_IndexList.push_back(8); m_IndexList.push_back(9); m_IndexList.push_back(12);
	m_IndexList.push_back(12); m_IndexList.push_back(9); m_IndexList.push_back(13);
	m_IndexList.push_back(9); m_IndexList.push_back(10); m_IndexList.push_back(13);
	m_IndexList.push_back(13); m_IndexList.push_back(10); m_IndexList.push_back(14);
	m_IndexList.push_back(10); m_IndexList.push_back(11); m_IndexList.push_back(14);
	m_IndexList.push_back(14); m_IndexList.push_back(11); m_IndexList.push_back(15);

	return true;
}

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
	//if (m_dwSelectState & J_FOCUS)
	//{
	//	m_vColor.x = 0;
	//	m_vColor.y = 1;
	//	m_vColor.z = 1;
	//	m_vColor.w = 1.0f;
	//}
	//else 
	//{
	//	m_vColor.x = 1;
	//	m_vColor.y = 1;
	//	m_vColor.z = 1;
	//	m_vColor.w = 1.0f;
	//}
	//if (m_dwSelectState == JSelectState::J_DEFAULT)
	//{
		//m_pColorTex = m_pStatePlayList[0].pTex;
		//m_dwPreSelectState = m_dwSelectState;
	//}
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
	std::string state;
	if (m_dwPreSelectState == m_dwSelectState)
	{
		return;
	}
	if (m_pStatePlayList.size() <= 0) return;

	switch (m_dwSelectState)
	{
	case JSelectState::J_SELECTED:
	{
		if (m_pStatePlayList[3].pTex == nullptr) break;
		m_pColorTex = m_pStatePlayList[3].pTex;
		m_pStatePlayList[3].pSound->PlayEffect();
		JWorld::m_pWorld->m_bLoadZone = true;
		state += "J_SELECTED\n";
	}break;
	case JSelectState::J_HOVER:
	{
		if (m_pStatePlayList[1].pTex == nullptr) break;
		m_pColorTex = m_pStatePlayList[1].pTex;
		m_pStatePlayList[1].pSound->PlayEffect();

		state += "J_HOVER\n";
	}break;
	case JSelectState::J_ACTIVE:
	{
		if (m_pStatePlayList[2].pTex == nullptr) break;
		m_pColorTex = m_pStatePlayList[2].pTex;
		//m_pStatePlayList[2].pSound->PlayEffect();
		state += "J_ACTIVE\n";
	}break;
	case JSelectState::J_FOCUS:
	{
		if (m_pStatePlayList[2].pTex == nullptr) break;
		m_pColorTex = m_pStatePlayList[2].pTex;
		//m_pStatePlayList[2].pSound->PlayEffect();
		state += "J_FOCUS\n";
	}break;
	default:
	{
		m_pColorTex = m_pStatePlayList[0].pTex;
		state += std::to_string(m_dwSelectState);
	}
	}
	m_dwPreSelectState = m_dwSelectState;
	//DisplayText(state.c_str());
}


bool JListCtrlObject::Create(int xCount, int yCount)
{
	UpdateData();

	int iHalfWidth = m_fWidth / xCount;
	int iHalfHeight = m_fHeight / yCount;
	JVector2 pStart = { (float)m_rtDraw.left, (float)m_rtDraw.top };
	pStart.x += m_fWidth / xCount / 2.0f;
	pStart.y += m_fHeight / yCount / 2.0f;
	for (int iCol = 0; iCol < xCount; iCol++)
	{
		for (int iRow = 0; iRow < yCount; iRow++)
		{
			JUIModel* pNewBtn = I_UI.GetPtr(L"btnStart")->Clone();
			pNewBtn->m_pParent = this;
			pNewBtn->m_csName = L"Btn";
			pNewBtn->m_csName += std::to_wstring(iRow * yCount + iCol);
			pNewBtn->SetRectDraw({ 0,0, iHalfWidth,iHalfHeight });
			pNewBtn->SetPosition(JVector2(
				pStart.x + iHalfWidth * iCol,
				pStart.y + iHalfHeight * iRow));
			pNewBtn->UpdateData();
			//pNewBtn->m_dwSelectType = TSelectType::Select_Ignore;
			Add(pNewBtn);
		}
	}
	return true;
}
void JListCtrlObject::HitSelect(JBaseObject* pObj, DWORD dwState)
{
	std::string state = "\n";
	if (m_dwPreSelectState == m_dwSelectState)
	{
		return;
	}
	m_dwPreSelectState = m_dwSelectState;
	state = std::to_string(m_dwSelectState);
	
	DisplayText(state.c_str());
}