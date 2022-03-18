#include "JZoneWorld.h"
#include "JUIObject.h"

bool JZoneWorld::Init()
{

	return true;
}
bool JZoneWorld::Load(std::wstring filename)
{
	Sleep(1000);

	
	//std::shared_ptr<JNode> b = a.FIndIndex(750, 750); // 찾는법
	g_fBackGroundColor.x = 0.48f;
	g_fBackGroundColor.y = 0.48f;
	g_fBackGroundColor.z = 0.48f;
	g_fBackGroundColor.w = 1.0f;

	JShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	JShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");
	JTexture* m_pColorTex = I_Texture.Load(L"../../data/BattleCity/Black.jpg");
	m_pBackGroundImage = new JImageObject;
	m_pBackGroundImage->m_csName = L"JImageObject:bk";
	m_pBackGroundImage->Init();
	m_pBackGroundImage->SetRectDraw({ 0,0, 780,780 });
	m_pBackGroundImage->SetPosition(JVector2((g_rtClient.right/2)-100, g_rtClient.bottom/2));
	m_pBackGroundImage->m_pColorTex = m_pColorTex;
	m_pBackGroundImage->m_pMaskTex = nullptr;
	m_pBackGroundImage->m_pVShader = pVShader;
	m_pBackGroundImage->m_pPShader = pPShader;
	if (!m_pBackGroundImage->Create(m_pd3dDevice, m_pContext))
	{
		return false;
	}
	m_rtIngame.top = m_pBackGroundImage->m_rtDraw.top;
	m_rtIngame.bottom = m_pBackGroundImage->m_rtDraw.bottom + m_pBackGroundImage->m_rtDraw.top;
	m_rtIngame.left = m_pBackGroundImage->m_rtDraw.left;
	m_rtIngame.right = m_pBackGroundImage->m_rtDraw.right + m_pBackGroundImage->m_rtDraw.left;
	
	//사운드
	//m_testSound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	JSound* pSound = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\Attack.wav");
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\StageGameBGM.wav");
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	//I_Sound.GetPtr(pSound->m_csName)->Play();
	m_pBackGroundMusic->Play(false);

	I_Sprite.Load(L"PlayerData.txt");
	m_PlayerObj.m_pSprite = I_Sprite.GetPtr(L"level1_top");

	m_PlayerObj.Init();
	m_PlayerObj.SetPosition(JVector2(m_PlayerObj.m_pSprite->m_vPos.x, m_PlayerObj.m_pSprite->m_vPos.y));

	m_PlayerObj.SetRectSource({ 1,33,15,14 });
	m_PlayerObj.SetRectDraw({(LONG)(m_pBackGroundImage->m_vPos.x - m_pBackGroundImage->m_fWidth/2), (LONG)(m_pBackGroundImage->m_vPos.y + (m_pBackGroundImage->m_fHeight/2) - 60), 60, 60 });
	m_PlayerObj.m_vMuzzlePosition = JVector2((LONG)(m_pBackGroundImage->m_vPos.x - m_pBackGroundImage->m_fWidth / 2)+30, (LONG)(m_pBackGroundImage->m_vPos.y + (m_pBackGroundImage->m_fHeight / 2) - 60));
	m_PlayerObj.m_vDirection = JVector2(0, -1);
	m_PlayerObj.UpdateData();
	m_PlayerObj.m_csName = L"PlayerUser";
	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",//L"Shader.txt",
		//L"../../data/bitmap1.bmp"
		L"../../data/BattleCity/ObjectList_White.png"
		//	L"../../data/bitmap2.bmp"
	))
	{
		return false;
	}
	m_PlayerObj.m_rtIngame = m_rtIngame;
	for (int iNpc = 0; iNpc < 20; iNpc++)
	for (int iNpc = 0; iNpc < 10; iNpc++)
	{
		std::shared_ptr<JObjectNpc2D> npc = 
			std::make_shared<JObjectNpc2D>();
		npc->m_csName = L"NPC_";
		npc->m_csName += std::to_wstring(iNpc);
		npc->Init();
		npc->SetPosition(JVector2(50 + iNpc * 150, 50));
		if (iNpc % 2 == 0)
		{
			npc->SetRectSource({ 129,144,13,16 });
			npc->SetRectDraw({ 0,0, 60,60 });
		}
		else
		{
			npc->SetRectSource({ 129,130,13,13 });
			npc->SetRectDraw({ 0,0, 60,60 });
		}

		npc.get()->UpdateData();
		if (!npc->Create(m_pd3dDevice, m_pContext,
			L"../../data/shader/DefaultUI.txt",
			L"../../data/BattleCity/ObjectList_White.png"//,
			//L"../../data/bitmap2.bmp"
		))
		{
			return false;
		}
		//Npc Bomb
		// 포탄 이펙트
		I_Sprite.Load(L"AtackEffectData.txt");
		npc.get()->m_NpcAttackExplosionObj.m_bDead = true;
		npc.get()->m_NpcAttackExplosionObj.m_pSprite = I_Sprite.GetPtr(L"AttackEffect");

		npc.get()->m_NpcAttackExplosionObj.Init();
		//m_AttackExplosionObj.SetPosition(JVector2(400, 500));
		//JSprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");

		npc.get()->m_NpcAttackExplosionObj.SetRectSource(npc.get()->m_NpcAttackExplosionObj.m_pSprite->m_rtArray[0]);
		npc.get()->m_NpcAttackExplosionObj.SetRectDraw({ 0,0, 34, 46 });

		if (!npc.get()->m_NpcAttackExplosionObj.Create(m_pd3dDevice, m_pContext,
			L"../../data/shader/DefaultUI.txt",
			L"../../data/BattleCity/ObjectList_White.png"//,
			//L"../../data/bitmap2.bmp"
		))
		{
			return false;
		}

		npc.get()->m_rtIngame = m_rtIngame;
		m_NpcObj.push_back(npc);
	}



	// 포탄 이펙트
	//I_Sprite.Load(L"AtackEffectData.txt");
	m_AttackExplosionObj.m_bDead = true;
	m_AttackExplosionObj.m_pSprite = I_Sprite.GetPtr(L"AttackEffect");

	m_AttackExplosionObj.Init();
	//m_AttackExplosionObj.SetPosition(JVector2(400, 500));
	//JSprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");

	m_AttackExplosionObj.SetRectSource(m_AttackExplosionObj.m_pSprite->m_rtArray[0]);
	m_AttackExplosionObj.SetRectDraw({ 0,0, 34, 46 });

	if (!m_AttackExplosionObj.Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",
		L"../../data/BattleCity/ObjectList_White.png"//,
		//L"../../data/bitmap2.bmp"
	))
	{
		return false;
	}
	for (int iCannonBall = 0; iCannonBall < 3; iCannonBall++)
	{
		std::shared_ptr<JAttackObj2D> CannonBall =
			std::make_shared<JAttackObj2D>();
		CannonBall->m_bDead = true;
		CannonBall->m_csName = L"CannonBall_";
		CannonBall->m_csName += std::to_wstring(iCannonBall);
		CannonBall->Init();
		CannonBall->SetPosition(m_PlayerObj.m_vMuzzlePosition);
		
		CannonBall->SetRectSource({ 323, 102, 3, 4 });
		CannonBall->SetRectDraw({ 0, 0, 16, 16 });
		
		CannonBall.get()->UpdateData();
		if (!CannonBall->Create(m_pd3dDevice, m_pContext,
			L"../../data/shader/DefaultUI.txt",
			L"../../data/BattleCity/ObjectList_White.png"//,
			//L"../../data/bitmap2.bmp"
		))
		{
			return false;
		}
		CannonBall.get()->m_rtIngame = m_rtIngame;
		m_PlayerObj.m_CannonBallObj.push_back(CannonBall);
	}

	//타일 등록 
	
	m_Map.CreateMap(MAX_SIZE_X, MAX_SIZE_Y, { m_rtIngame.left, m_rtIngame.top, 780, 780 });
	int iTile = 0;
	for (int i=0; i < MAX_SIZE_X; i++)
	{
		for (int j = 0; j < MAX_SIZE_Y; j++)
		{
			if (m_Tile.iTileArray[j][i])
			{
				//타일 index 찾기
				std::shared_ptr<JNode> newNode = m_Map.FIndIndex(i+(j*MAX_SIZE_Y));
				//ui 생성
				std::shared_ptr<JTileObj2D> tile = std::make_shared<JTileObj2D>();
				tile->m_csName = L"TileObject";
				//tile->m_csName += std::to_wstring(iTile);
				tile->Init();
				tile->m_bDead = false;
				//tile->SetPosition(JVector2(newNode.get()->m_rtPos.left , newNode.get()->m_rtPos.top));
				if (m_Tile.iTileArray[j][i] == 1)
				{
					tile->SetRectSource({ 260,4,8,8 });
					tile->SetRectDraw({ newNode.get()->m_rtPos.left,newNode.get()->m_rtPos.top, (LONG)newNode.get()->m_fWidth,(LONG)newNode.get()->m_fHeight });
				}
				else if(m_Tile.iTileArray[j][i] == 7)
				{
					tile->SetRectSource({ 304,32,8,8 });
					tile->SetRectDraw({ newNode.get()->m_rtPos.left,newNode.get()->m_rtPos.top, (LONG)newNode.get()->m_fWidth,(LONG)newNode.get()->m_fHeight });
				}
				else if (m_Tile.iTileArray[j][i] == 8)
				{
					tile->SetRectSource({ 312,32,8,8 });
					tile->SetRectDraw({ newNode.get()->m_rtPos.left,newNode.get()->m_rtPos.top, (LONG)newNode.get()->m_fWidth,(LONG)newNode.get()->m_fHeight });
				}
				else if (m_Tile.iTileArray[j][i] == 9)
				{
					tile->SetRectSource({ 304,40,8,8 });
					tile->SetRectDraw({ newNode.get()->m_rtPos.left,newNode.get()->m_rtPos.top, (LONG)newNode.get()->m_fWidth,(LONG)newNode.get()->m_fHeight });
				}
				else if (m_Tile.iTileArray[j][i] == 10)
				{
					tile->SetRectSource({ 312,40,8,8 });
					tile->SetRectDraw({ newNode.get()->m_rtPos.left,newNode.get()->m_rtPos.top, (LONG)newNode.get()->m_fWidth,(LONG)newNode.get()->m_fHeight });
				}
				tile.get()->UpdateData();
				if (!tile->Create(m_pd3dDevice, m_pContext,
					L"../../data/shader/DefaultUI.txt",
					L"../../data/BattleCity/ObjectList.png"//,
					//L"../../data/bitmap2.bmp"
				))
				{
					return false;
				}
				m_MapObj.push_back(tile);
				iTile++;
			}
		}
	}


	return true;
}


bool JZoneWorld::Frame()
{
	
	//m_SoundMgr.GetPtr(L"OnlyLove.MP3")->Play();
	//JSound* pSound = I_Sound.GetPtr(L"BattleCityBGM.mp3");
	//pSound->Frame();
	if (!m_pBackGroundMusic->isPlaying() && (m_pBackGroundMusic->m_csName != L"StageGameBGM.wav"))
	{
		m_pBackGroundMusic = I_Sound.Get().GetPtr(L"StageGameBGM.wav");
		m_pBackGroundMusic->Play(true);
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
	
	if (JInput::Get().GetKey(VK_UP) == KEY_PUSH)// && (m_iCheck == 0 || m_iCheck == 1))
	{
		m_PlayerObj.m_pSprite = I_Sprite.GetPtr(L"level1_top");
		m_PlayerObj.SetRectSource(m_PlayerObj.m_pSprite->m_rtArray[0]);	
		//m_PlayerObj.m_vDirection = JVector2(0, -1);
	}
	else if (JInput::Get().GetKey(VK_DOWN) == KEY_PUSH)// && (m_iCheck == 0 || m_iCheck == 2))
	{
		m_PlayerObj.m_pSprite = I_Sprite.GetPtr(L"level1_bottom");
		m_PlayerObj.SetRectSource(m_PlayerObj.m_pSprite->m_rtArray[0]);
		//m_PlayerObj.m_vDirection = JVector2(0, 1);
		
	}
	else if (JInput::Get().GetKey(VK_LEFT) == KEY_PUSH)// && (m_iCheck == 0 || m_iCheck == 3))
	{
		m_PlayerObj.m_pSprite = I_Sprite.GetPtr(L"level1_left");
		m_PlayerObj.SetRectSource(m_PlayerObj.m_pSprite->m_rtArray[0]);
		//m_PlayerObj.m_vDirection = JVector2(-1, 0);
	
	}
	else if (JInput::Get().GetKey(VK_RIGHT) == KEY_PUSH)// && (m_iCheck == 0 || m_iCheck == 4))
	{
		m_PlayerObj.m_pSprite = I_Sprite.Get().GetPtr(L"level1_right");
		m_PlayerObj.SetRectSource(m_PlayerObj.m_pSprite->m_rtArray[0]);
		//m_PlayerObj.m_vDirection = JVector2(1, 0);
	
	}
	m_AttackExplosionObj.SetTargetPosition(&m_PlayerObj.m_vMuzzlePosition);
	
	if (JInput::Get().GetKey('Z') == KEY_PUSH)
	{
		//pSound->Stop();
		//총알이 살아있으면 호출하지 않는다. 총알이 하나라도 죽어있으면 true반환
		
		if (g_fGameTimer >= m_PlayerObj.m_fAttackTime + m_PlayerObj.m_fWaitTime)
		{
			if (m_PlayerObj.isCannonBall())
			{
				for (int i = 0; i < m_PlayerObj.m_CannonBallObj.size(); i++)
				{
					if (m_PlayerObj.m_CannonBallObj[i]->m_bDead == true)
					{
						m_PlayerObj.m_CannonBallObj[i]->m_bDead = false;
						break;
					}
				}
				JSound* pSound1 = I_Sound.GetPtr(L"Attack.wav");
				if (pSound1 != nullptr)
				{
					pSound1->PlayEffect();
				}
				m_AttackExplosionObj.m_bDead = false;
			}
			m_PlayerObj.m_fAttackTime = g_fGameTimer;
		}
	}
	m_pBackGroundImage->Frame();
	m_AttackExplosionObj.Frame();
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
	m_pBackGroundImage->Render();
	JWorld::Render();
	m_PlayerObj.Render();
	m_AttackExplosionObj.Render();
	
	return true;
}

bool JZoneWorld::Release()
{
	m_PlayerObj.Release();
	m_AttackExplosionObj.Release();
	return true;
}
