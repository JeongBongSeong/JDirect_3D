#include "JIntroWorld.h"

bool JIntroWorld::Init()
{
	return true;
}
bool JIntroWorld::Load(std::wstring filename)
{
	//»ç¿îµå
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	//I_Sound.GetPtr(pSound->m_csName)->Play();
	//220221
	JObject2D* obj = new JObject2D;
	obj->Init();
	obj->SetRectDraw({ 0,0, g_rtClient.right,g_rtClient.bottom });
	obj->SetPosition(JVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	if (!obj->Create(m_pd3dDevice, m_pContext,
		L"../../data/KGCABK.bmp"))
	{
		return false;
	}
	m_UIObj.insert(std::make_pair(L"bk", obj));
	//220221
	m_pBackGroundMusic->Play(true);

    return true;
}

bool JIntroWorld::Frame()
{
	m_pBackGroundMusic->Frame();
	for (auto obj : m_UIObj)
	{
		JObject2D* pObj = obj.second;
		if (pObj != nullptr)
		{
			pObj->m_ConstantList.Color = JVector4(
				cosf(g_fGameTimer) * 0.5f + 0.5f,
				cosf(g_fGameTimer) * 0.5f + 0.5f,
				cosf(g_fGameTimer) * 0.5f + 0.5f, 1.0f);
			pObj->m_ConstantList.Timer = JVector4(
				g_fGameTimer,
				0,
				0,
				1.0f);
			m_pContext->UpdateSubresource(
				pObj->m_pConstantBuffer, 0, NULL, &pObj->m_ConstantList, 0, 0);
		}
	}
    return true;
}

bool JIntroWorld::Render()
{
	for (auto obj : m_UIObj)
	{
		JObject2D* pObj = obj.second;
		if (pObj != nullptr)
		{
			pObj->Render();
		}
	}
	return true;
}

bool JIntroWorld::Release()
{
	JWorld::Release();
    return true;
}
