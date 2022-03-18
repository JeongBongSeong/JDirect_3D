#include "JIntroWorld.h"


bool JIntroWorld::CreateModelType()
{
	/// <summary>
	/// 배경이미지
	/// </summary>
	/// <param name="file"></param>
	/// <returns></returns>
	JShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	JShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");

	JImageObject* obj = new JImageObject;
	obj->m_csName = L"JImageObject:bk";
	obj->Init();
	obj->SetRectDraw({ 0,0, 800,205 });
	obj->SetPosition(JVector2(0,0));
	obj->m_pColorTex = m_pColorTex;
	obj->m_pMaskTex = nullptr;
	obj->m_pVShader = pVShader;
	obj->m_pPShader = pPShader;
	if (!obj->Create(m_pd3dDevice, m_pContext))
	{
		return false;
	}
	obj->SetCollisionType(JCollisionType::Ignore, JSelectType::Select_Ignore);
	I_UI.m_list.insert(std::make_pair(L"bk", obj));

	// btn DLG
	JButtonObject* btnDlg = new JButtonObject;
	btnDlg->Init();
	btnDlg->m_rtOffset = { 50, 50, 50, 50 };
	btnDlg->SetRectDraw({ 0,0, g_rtClient.right / 2,g_rtClient.bottom / 2 });
	btnDlg->SetPosition(JVector2(0,0));
	if (!btnDlg->Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",
		L"../../data/ui/Zosma/Main/Quantity.png"))
	{
		return false;
	}
	btnDlg->SetCollisionType(JCollisionType::Ignore, JSelectType::Select_Overlap);
	I_UI.m_list.insert(std::make_pair(L"btnDlg", btnDlg));


	//btn obj
	m_btnObj = new JButtonObject;
	m_btnObj->m_csName = L"JButtonObject:btnStart";
	m_btnObj->Init();
	m_btnObj->m_rtOffset = { 0, 0, 0, 0 };
	m_btnObj->SetRectDraw({ 0,0, 475,92 });
	m_btnObj->SetPosition(JVector2(0,0));
	JTexture* pTex = I_Texture.Load(L"../../data/BattleCity/GameStart1.png");
	JSound* pSound = I_Sound.Load("../../data/Sound/00_Menu.MP3");
	// 가변인자를 통해서 생성자 직접 호출
	m_btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/BattleCity/GameStart2.png");
	pSound = I_Sound.Load("../../data/Sound/FootStepSound.wav");
	// 가변인자를 통해서 생성자 직접 호출
	m_btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/BattleCity/GameStart3.png");
	pSound = I_Sound.Load("../../data/Sound/FootStepSound_2.wav");
	// 가변인자를 통해서 생성자 직접 호출
	m_btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/BattleCity/GameStart3.png");
	pSound = I_Sound.Load("../../data/Sound/BattleCity/SelectMenu.wav");
	// 가변인자를 통해서 생성자 직접 호출
	m_btnObj->m_pStatePlayList.emplace_back(pTex, pSound);

	if (!m_btnObj->Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",
		L"../../data/BattleCity/GameStart1.png"))
	{
		return false;
	}
	m_btnObj->SetCollisionType(JCollisionType::Ignore, JSelectType::Select_Overlap);
	I_UI.m_list.insert(std::make_pair(L"btnStart", m_btnObj));

	// 새로운 모델을 생성해서 등록한다.
	JUIModelComposed* pComposedObj = new JUIModelComposed;
	pComposedObj->m_csName = L"JUIModelComposed";
	JButtonObject* pDlgWindow = (JButtonObject*)I_UI.GetPtr(L"btnDlg")->Clone();
	pDlgWindow->m_pParent = nullptr;
	pDlgWindow->m_rtOffset = { 0, 0, 0, 0 };
	pDlgWindow->SetRectDraw({ 0,0,393,80 });
	pDlgWindow->AddPosition(JVector2(g_rtClient.right/3, g_rtClient.bottom - 250));
	pDlgWindow->UpdateData();
	pComposedObj->Add(pDlgWindow);

	JUIModel* pNewDlgBtn = I_UI.GetPtr(L"btnStart")->Clone();// new TButtonObject(*I_UI.GetPtr(L"btnStart"));
	pNewDlgBtn->m_csName = L"btnStartClone_ComposedList";
	pNewDlgBtn->m_pParent = pDlgWindow;
	pNewDlgBtn->SetRectDraw({ 0,0, 336,61 });
	pNewDlgBtn->AddPosition(pDlgWindow->m_vPos - JVector2(pNewDlgBtn->m_fWidth/2, pNewDlgBtn->m_fHeight/2));
	pNewDlgBtn->UpdateData();
	pComposedObj->Add(pNewDlgBtn);
	I_UI.m_list.insert(std::make_pair(L"dlgWindow", pComposedObj));


	return true;
}

bool JIntroWorld::Init()
{
	g_fBackGroundColor.x = 0.0f;
	g_fBackGroundColor.y = 0.0f;
	g_fBackGroundColor.z = 0.0f;
	g_fBackGroundColor.w = 1.0f;
	JWorld::Init();
	return true;
}

bool JIntroWorld::Load(std::wstring filename)
{
	
	//사운드
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	
	//화면 이미지
	m_pColorTex = I_Texture.Load(L"../../data/BattleCity/Battle_city_logo_by_ringostarr39-d7z8izo.png");

	//for (int i = 0; i < 10; i++)
	//{
	//	std::wstring name = L"../../data/";
	//	name += std::to_wstring(i);
	//	name += L".bmp";
	//	m_pChangeColorTex[i] = I_Texture.Load(name);
	//}
	CreateModelType();

	
	JUIModel* pNewBK = I_UI.GetPtr(L"bk")->Clone();// new JButtonObject(*I_UI.GetPtr(L"btnStart"));
	pNewBK->m_csName = L"JImageObjectClock:bk";
	pNewBK->SetPosition(JVector2(g_rtClient.right/2, 200));
	pNewBK->SetPosition(JVector2(g_rtClient.right/2, 150));
	pNewBK->UpdateData();
	m_UIObj.push_back(std::shared_ptr<JObject2D>(pNewBK));

	//컴포짓

	//JUIModel* pNewBtn1 = I_UI.GetPtr(L"btnStart")->Clone();// new JButtonObject(*I_UI.GetPtr(L"btnStart"));
	//pNewBtn1->m_csName = L"btnStartClone1";
	//pNewBtn1->SetRectDraw({ 0,0, 100,50 });
	//pNewBtn1->SetPosition(JVector2(300, 25));
	//pNewBtn1->UpdateData();
	//m_UIObj.push_back(std::shared_ptr<JObject2D>(pNewBtn1));

	//JUIModel* pNewBtn2 = I_UI.GetPtr(L"btnStart")->Clone();// new JButtonObject(*I_UI.GetPtr(L"btnStart"));
	//pNewBtn2->m_csName = L"btnStartClone2";
	//pNewBtn2->SetRectDraw({ 0,0, 100,100 });
	//pNewBtn2->SetPosition(JVector2(400, 150));
	//pNewBtn2->UpdateData();
	//m_UIObj.push_back(std::shared_ptr<JObject2D>(pNewBtn2));

	//JUIModel* pNewBtn3 =I_UI.GetPtr(L"btnStart")->Clone();// new JButtonObject(*I_UI.GetPtr(L"btnStart"));
	//pNewBtn3->m_csName = L"btnStartClone3";
	//pNewBtn3->SetRectDraw({ 0,0, 100,50 });
	//pNewBtn3->SetPosition(JVector2(500, 200));
	//pNewBtn3->UpdateData();
	//m_UIObj.push_back(std::shared_ptr<JObject2D>(pNewBtn3));

	JUIModel* pNewDlgBtnClone = I_UI.GetPtr(L"dlgWindow")->Clone();// new JButtonObject(*I_UI.GetPtr(L"btnStart"));
	pNewDlgBtnClone->m_csName = L"JUIModelComposedClone";
	pNewDlgBtnClone->m_pParent = nullptr;
	pNewDlgBtnClone->SetPosition(JVector2(0, 0));
	pNewDlgBtnClone->UpdateData();
	m_UIObj.push_back(std::shared_ptr<JObject2D>(pNewDlgBtnClone));

	//std::shared_ptr<JListCtrlObject> pListCtrl = std::make_shared<JListCtrlObject>();
	//pListCtrl->m_csName = L"JListCtrlObject";
	//pListCtrl->m_pParent = pNewBK;
	//pListCtrl->SetRectDraw({ 100,100, 100,300 });
	////pListCtrl->SetPosition(JVector2(400, 300));
	//pListCtrl->Create(1, 5);
	//m_UIObj.push_back(pListCtrl);



	//// 이펙트
	//I_Sprite.Load(L"SpriteData.txt");
	//m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");

	//m_ExplosionObj.Init();
	//m_ExplosionObj.SetPosition(JVector2(400, 500));
	////JSprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");

	//m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	//m_ExplosionObj.SetRectDraw({ 0,0, 34, 46 });

	//if (!m_ExplosionObj.Create(m_pd3dDevice, m_pContext,
	//	L"Shader.txt",
	//	L"../../data/bitmap1.bmp",
	//	L"../../data/bitmap2.bmp"))
	//{
	//	return false;
	//}
    return true;
}

bool JIntroWorld::Frame()
{
	m_pBackGroundMusic->Frame();
	//m_pBackGroundMusic->Play(false);
	if (m_bLoadZone && m_pNextWorld != nullptr)
	{
		I_ObjectMgr.Release();
		m_pBackGroundMusic->Stop();
		m_pNextWorld->Load(L"zone.txt");
		JWorld::m_pWorld = m_pNextWorld;
	}
	
	//배경음악
	

	static int iIndex = 0;
	/*if (JInput::Get().GetKey(VK_F2) == KEY_PUSH)
	{
		iIndex++;
		if (iIndex >= 10)
		{
			iIndex = 0;
		}
		auto data = m_UIObj.find(L"bk");
		if (data != m_UIObj.end())
		{
			data->second->m_pColorTex = m_pChangeColorTex[iIndex];
		}
	}*/
	/*if (JInput::Get().GetKey(VK_F3) == KEY_PUSH)
	{
		iIndex++;
		if (iIndex >= m_ExplosionObj.m_pSprite->m_rtArray.size())
		{
			iIndex = 0;
		}
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[iIndex]);
		
	}
	if (JInput::Get().GetKey(VK_F4) == KEY_PUSH)
	{
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);

	}
	if (JInput::Get().GetKey(VK_F5) == KEY_PUSH)
	{
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtBomb");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);

	}
	if (JInput::Get().GetKey(VK_F6) == KEY_PUSH)
	{
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtClash");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);

	}*/
	m_btnObj->Frame();
	//m_ExplosionObj.Frame();
	JWorld::Frame();

    return true;
}

bool JIntroWorld::Render()
{
	JWorld::Render();
	//m_ExplosionObj.Render();
	return true;
}

bool JIntroWorld::Release()
{
	JWorld::Release();
	//m_ExplosionObj.Release();
    return true;
}
