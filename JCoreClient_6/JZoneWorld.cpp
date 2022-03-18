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
	pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	//I_Sound.GetPtr(pSound->m_csName)->Play();
	pBackGroundMusic->Play(true);

	//플레이어
	m_PlayerObj.Init();
	m_PlayerObj.SetPosition(JVector2(400, 500));
	m_PlayerObj.SetRectSource({ 91,1,42,56 });
	m_PlayerObj.SetRectDraw({ 0,0, 42,56 });


	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext,
		L"../../data/bitmap1.bmp",
		L"../../data/bitmap2.bmp"))
	{
		return false;
	}

	for (int iNpc = 0; iNpc < 10; iNpc++)
	{
		JObjectNpc2D* npc = new JObjectNpc2D;
		npc->Init();
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

		npc->SetPosition(JVector2(50 + iNpc * 150, 50));
		if (!npc->Create(m_pd3dDevice, m_pContext,
			L"../../data/bitmap1.bmp",
			L"../../data/bitmap2.bmp"))
		{
			return false;
		}
		m_NpcLlist.push_back(npc);
	}



	return true;
}

bool JZoneWorld::Frame()
{
	m_PlayerObj.Frame();
	//m_SoundMgr.GetPtr(L"OnlyLove.MP3")->Play();
	JSound* pSound = I_Sound.GetPtr(L"BattleCityBGM.mp3");
	pSound->Frame();
	if (JInput::Get().GetKey('Z') == KEY_PUSH)
	{
		//pSound->Stop();
		JSound* pSound1 = I_Sound.GetPtr(L"Attack.wav");
		if (pSound1 != nullptr)
		{
			pSound1->PlayEffect();
		}
	}
	if (JInput::Get().GetKey(VK_ADD) == KEY_HOLD)
	{
		pSound->VolumeUp(g_fSecPerFrame);
	}
	if (JInput::Get().GetKey(VK_SUBTRACT) == KEY_HOLD)
	{
		pSound->VolumeDown(g_fSecPerFrame);
	}


	for (int iObj = 0; iObj < m_NpcLlist.size(); iObj++)
	{
		//RECT rt = m_NpcLlist[iObj]->m_rtDraw;
		///rt.right = rt.right + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
		//rt.bottom = rt.bottom + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
		//m_NpcLlist[iObj]->UpdateRectDraw(rt);
		m_NpcLlist[iObj]->Frame();
		//충돌체크
	/*	if (JCollision::ToRect(m_PlayerObj.m_rtCollision, m_NpcLlist[iObj]->m_rtCollision))
		{
			m_NpcLlist[iObj]->m_bAlphaBlend = FALSE;
		}
		else
		{
			m_NpcLlist[iObj]->m_bAlphaBlend = TRUE;
		}*/
	}
	return true;
}

bool JZoneWorld::Render()
{
	// 죽지않았을때만 Render한다.
	for (int iObj = 0; iObj < m_NpcLlist.size(); iObj++)
	{
		if (m_NpcLlist[iObj]->m_bDead == false)
		{
			m_NpcLlist[iObj]->Render();
		}
	}
	m_PlayerObj.Render();

	//RECT rt = g_rtClient;
	//rt.top = 200;
	//rt.left = 480;
	//m_dxWrite.Draw(L"JBSProject", rt, D2D1::ColorF(0, 0, 0, 1), m_dxWrite.m_pd2dMTShadowTF);
	//rt.top = 0;
	//rt.left = 420;
	//m_dxWrite.Draw(pBackGroundMusic->m_szBuffer, rt, D2D1::ColorF(0, 0, 0, 1));

	return true;
}

bool JZoneWorld::Release()
{
	for (int iObj = 0; iObj < m_NpcLlist.size(); iObj++)
	{
		m_NpcLlist[iObj]->Release();
		delete m_NpcLlist[iObj];
	}
	m_PlayerObj.Release();
	m_NpcLlist.clear();

	return true;
}
