#include "JZoneWorld.h"

bool JZoneWorld::Init()
{
	return true;
}
bool JZoneWorld::Load(std::wstring filename)
{
	//사운드
	//m_testSound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	JSound* pSound = I_Sound.Load("..\\..\\data\\Sound\\OnlyLove.MP3");
	pSound = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\Attack.wav");
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\OnlyLove.MP3");
	//I_Sound.GetPtr(pSound->m_csName)->Play();
	m_pBackGroundMusic->Play(true);

	//플레이어
	m_PlayerObj.Init();
	m_PlayerObj.SetPosition(JVector2(400, 500));
	m_PlayerObj.SetRectSource({ 91,1,42,56 });
	m_PlayerObj.SetRectDraw({ 0,0, 42,56 });
	m_PlayerObj.m_csName = L"PlayerUser";

	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext,
		L"Shader.txt",
		L"../../data/bitmap1.bmp",
		L"../../data/bitmap2.bmp"))
	{
		return false;
	}

	for (int iNpc = 0; iNpc < 10; iNpc++)
	{
		JObjectNpc2D* npc = new JObjectNpc2D;
		npc->m_csName = L"NPC_";
		npc->m_csName += std::to_wstring(iNpc);
		npc->Init();
		npc->SetPosition(JVector2(50 + iNpc * 150, 50));
		if (iNpc % 2 == 0)
		{
			npc->SetRectSource({ 46,63,69,79 });
			npc->SetRectDraw({ 0,0, 69,79 });
		}
		else
		{
			npc->SetRectSource({ 1,63,42,76 });
			npc->SetRectDraw({ 0,0, 42,76 });
		}


		if (!npc->Create(m_pd3dDevice, m_pContext,
			L"Shader.txt",
			L"../../data/bitmap1.bmp",
			L"../../data/bitmap2.bmp"))
		{
			return false;
		}
		m_NpcObj.push_back(npc);
	}



	return true;
}

bool JZoneWorld::Frame()
{
	
	//m_SoundMgr.GetPtr(L"OnlyLove.MP3")->Play();
	//JSound* pSound = I_Sound.GetPtr(L"BattleCityBGM.mp3");
	//pSound->Frame();
	if (JInput::Get().GetKey('Z') == KEY_PUSH)
	{
		//pSound->Stop();
		JSound* pSound1 = I_Sound.GetPtr(L"Attack.wav");
		if (pSound1 != nullptr)
		{
			pSound1->PlayEffect();
		}
	}

	m_pBackGroundMusic->Frame();

	if (JInput::Get().GetKey(VK_ADD) == KEY_HOLD)
	{
		m_pBackGroundMusic->VolumeUp(g_fSecPerFrame);
	}
	if (JInput::Get().GetKey(VK_SUBTRACT) == KEY_HOLD)
	{
		m_pBackGroundMusic->VolumeDown(g_fSecPerFrame);
	}

	m_PlayerObj.Frame();
	JWorld::Frame();
	//for (int iObj = 0; iObj < m_NpcLlist.size(); iObj++)
	//{
	//	//RECT rt = m_NpcLlist[iObj]->m_rtDraw;
	//	///rt.right = rt.right + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
	//	//rt.bottom = rt.bottom + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
	//	//m_NpcLlist[iObj]->UpdateRectDraw(rt);
	//	m_NpcLlist[iObj]->Frame();
	//	//충돌체크
	///*	if (JCollision::ToRect(m_PlayerObj.m_rtCollision, m_NpcLlist[iObj]->m_rtCollision))
	//	{
	//		m_NpcLlist[iObj]->m_bAlphaBlend = FALSE;
	//	}
	//	else
	//	{
	//		m_NpcLlist[iObj]->m_bAlphaBlend = TRUE;
	//	}*/
	//}
	return true;
}

bool JZoneWorld::Render()
{
	JWorld::Render();
	m_PlayerObj.Render();

	return true;
}

bool JZoneWorld::Release()
{
	m_PlayerObj.Release();

	return true;
}
