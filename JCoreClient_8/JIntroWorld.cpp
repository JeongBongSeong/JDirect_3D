#include "JIntroWorld.h"


bool JIntroWorld::Init()
{
	JWorld::Init();
	return true;
}

bool JIntroWorld::Load(std::wstring filename)
{
	
	//����
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");

	//ȭ�� �̹���
	m_pColorTex = I_Texture.Load(L"../../data/KGCABK.bmp");

	for (int i = 0; i < 10; i++)
	{
		std::wstring name = L"../../data/";
		name += std::to_wstring(i);
		name += L".bmp";
		m_pChangeColorTex[i] = I_Texture.Load(name);
	}

	JTexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	JShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	JShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");

	JImageObject* obj = new JImageObject;
	obj->Init();
	obj->SetRectDraw({ 0,0, g_rtClient.right,g_rtClient.bottom });
	obj->SetPosition(JVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	obj->m_pColorTex = m_pColorTex;
	obj->m_pMaskTex = nullptr;
	obj->m_pVShader = pVShader;
	obj->m_pPShader = pPShader;

	if (!obj->Create(m_pd3dDevice, m_pContext))
	{
		return false;
	}
	obj->SetCollisionType(JCollisionType::Ignore, JSelectType::Select_Ignore);
	m_UIObj.insert(std::make_pair(L"bk", obj));
	
	
	//btn
	m_btnObj = new JButtonObject;
	m_btnObj->Init();
	m_btnObj->SetRectDraw({ 0,0, 334,82 });
	m_btnObj->SetPosition(JVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	if (!m_btnObj->Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",
		L"../../data/ui/main_start_nor.png"))
	{
		return false;
	}
	m_btnObj->SetCollisionType(JCollisionType::Ignore, JSelectType::Select_Overlap);
	m_UIObj.insert(std::make_pair(L"btnStart", m_btnObj));

	// ����Ʈ
	I_Sprite.Load(L"SpriteData.txt");
	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");

	m_ExplosionObj.Init();
	m_ExplosionObj.SetPosition(JVector2(400, 500));
	//JSprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");

	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	m_ExplosionObj.SetRectDraw({ 0,0, 34, 46 });

	if (!m_ExplosionObj.Create(m_pd3dDevice, m_pContext,
		L"Shader.txt",
		L"../../data/bitmap1.bmp",
		L"../../data/bitmap2.bmp"))
	{
		return false;
	}

    return true;
}

bool JIntroWorld::Frame()
{
	m_pBackGroundMusic->Frame();
	m_pBackGroundMusic->Play(true);
	if (m_bLoadZone && m_pNextWorld != nullptr)
	{
		I_ObjectMgr.Release();
		m_pBackGroundMusic->Stop();
		m_pNextWorld->Load(L"zone.txt");
		JWorld::m_pWorld = m_pNextWorld;
	}
	
	//�������
	

	//static int iIndex = 0;
	//if (JInput::Get().GetKey(VK_F2) == KEY_PUSH)
	//{
	//	iIndex++;
	//	if (iIndex >= 10)
	//	{
	//		iIndex = 0;
	//	}
	//	auto data = m_UIObj.find(L"bk");
	//	if (data != m_UIObj.end())
	//	{
	//		data->second->m_pColorTex = m_pChangeColorTex[iIndex];
	//	}
	//}
	//if (JInput::Get().GetKey(VK_F3) == KEY_PUSH)
	//{
	//	iIndex++;
	//	if (iIndex >= m_ExplosionObj.m_pSprite->m_rtArray.size())
	//	{
	//		iIndex = 0;
	//	}
	//	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[iIndex]);
	//	m_ExplosionObj.SetRectDraw({ 0,0,
	//		m_ExplosionObj.m_pSprite->m_rtArray[iIndex].right,
	//		m_ExplosionObj.m_pSprite->m_rtArray[iIndex].bottom });
	//}
	//if (JInput::Get().GetKey(VK_F4) == KEY_PUSH)
	//{
	//	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
	//	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	//	m_ExplosionObj.SetRectDraw({ 0,0,
	//		m_ExplosionObj.m_pSprite->m_rtArray[0].right,
	//		m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	//}
	//if (JInput::Get().GetKey(VK_F5) == KEY_PUSH)
	//{
	//	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtBomb");
	//	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	//	m_ExplosionObj.SetRectDraw({ 0,0,
	//		m_ExplosionObj.m_pSprite->m_rtArray[0].right,
	//		m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	//}
	//if (JInput::Get().GetKey(VK_F6) == KEY_PUSH)
	//{
	//	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtClash");
	//	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	//	m_ExplosionObj.SetRectDraw({ 0,0,
	//		m_ExplosionObj.m_pSprite->m_rtArray[0].right,
	//		m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	//}
	m_btnObj->Frame();
	m_ExplosionObj.Frame();
	JWorld::Frame();

    return true;
}

bool JIntroWorld::Render()
{
	JWorld::Render();
	m_ExplosionObj.Render();
	return true;
}

bool JIntroWorld::Release()
{
	JWorld::Release();
	m_ExplosionObj.Release();
    return true;
}
