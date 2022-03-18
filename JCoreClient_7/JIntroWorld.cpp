#include "JIntroWorld.h"


bool JIntroWorld::Init()
{
	JWorld::Init();
	return true;
}

bool JIntroWorld::Load(std::wstring filename)
{
	
	//»ç¿îµå
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	
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
	m_UIObj.insert(std::make_pair(L"bk", obj));
	//btn
	JImageObject* btnObj = new JImageObject;
	btnObj->Init();
	btnObj->SetRectDraw({ 0,0, 334,82 });
	btnObj->SetPosition(JVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	if (!btnObj->Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",
		L"../../data/main_start_nor.png"))
	{
		return false;
	}
	m_UIObj.insert(std::make_pair(L"btnStart", btnObj));

	m_pBackGroundMusic->Play(true);

    return true;
}

bool JIntroWorld::Frame()
{
	m_pBackGroundMusic->Frame();
	static int iIndex = 0;
	if (JInput::Get().GetKey(VK_F2) == KEY_PUSH)
	{
		iIndex++;
		auto data = m_UIObj.find(L"bk");
		if (data != m_UIObj.end())
		{
			data->second->m_pColorTex = m_pChangeColorTex[iIndex];
		}
		if (iIndex >= 10)
		{
			iIndex = 0;
		}
	}

	/*
	{
		auto data = m_UIObj.find(L"bk");
		if (data != m_UIObj.end())
		{
			data->second->m_pColorTex = m_pColorTex;
		}
	}*/
	JWorld::Frame();

    return true;
}

bool JIntroWorld::Render()
{
	JWorld::Render();
	return true;
}

bool JIntroWorld::Release()
{
	JWorld::Release();
    return true;
}
